#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <codecvt>
#include <locale>

#ifdef _WIN32

#include <Windows.h>

#endif

using namespace std;

// 分割字符串，返回分割数组
vector<string> StringSplit(const string &phrase, const string &delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = phrase.find(delimiter, pos_start)) != string::npos) {
        token = phrase.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.emplace_back(token);
    }

    res.emplace_back(phrase.substr(pos_start));
    return res;
}

// 是否字符串以给定字符串开始
static bool IsStringStartWith(const std::string &str, const std::string &prefix) {
    return ((prefix.size() <= str.size()) && std::equal(prefix.begin(), prefix.end(), str.begin()));
}

// 移除16进制前缀
string RemoveHexPrefix(string &hex) {
    if (IsStringStartWith(hex, "0x") or IsStringStartWith(hex, "0X")) {
        hex = hex.substr(2);
    } else if (IsStringStartWith(hex, "x") or IsStringStartWith(hex, "X")) {
        hex = hex.substr(1);
    }
    return hex;
}


const wchar_t UNICODE_REPLACEMENT_CHAR = 0xFFFD;

// 单个hex转ASCII
wchar_t StringHex2Ascii(string &hex) {
    // 可能的16进制表示形式: 0x12 AB ab 0xFa 0x1 6 0X12 x16 X0C
    hex = RemoveHexPrefix(hex);
    if (hex.empty() or hex.size() > 2) {
        return UNICODE_REPLACEMENT_CHAR;
    }
    int ascii = 0;
    for (const auto &val: hex) {
        ascii *= 0x10;
        if ('0' <= val and val <= '9') {
            ascii += val - '0';
        } else if ('A' <= val and val <= 'F') {
            ascii += 10 + val - 'A';
        } else if ('a' <= val and val <= 'f') {
            ascii += 10 + val - 'a';
        } else {
            return UNICODE_REPLACEMENT_CHAR;
        }
    }
    if (ascii > std::numeric_limits<signed char>::max()) {
        return UNICODE_REPLACEMENT_CHAR;
    }
    return ascii;
}


// 函数入口
wstring Hex2Ascii(const std::string &input) {
    string delimiter = " ";     // 以空格为分隔符
    auto split = StringSplit(input, delimiter);
    wstring output;
    for (auto &&hex: split) {
        output += StringHex2Ascii(hex);
    }
    return std::move(output);
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 0;
    }
    // 优先转换为 utf-8
    std::wstring unicodeStr = Hex2Ascii(argv[1]);
    std::wstring_convert<std::codecvt_utf8<wchar_t>> u8Conv;
    auto utf8Str = u8Conv.to_bytes(unicodeStr);
#ifdef WIN32
    SetConsoleOutputCP(CP_UTF8);    // windows 设置控制台输出为UTF-8编码，其他Unix/Linux默认为UTF-8
#endif
    std::cout << utf8Str << std::endl;
    return 0;
}
