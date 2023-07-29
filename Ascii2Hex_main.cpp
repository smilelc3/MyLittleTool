#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

// 函数入口

wstring Ascii2Hex(const std::string &input) {
    wostringstream output;
    for (const auto &ch: input) {
        output << "0x" << hex << setw(2) << (unsigned char) ch << " ";
    }
    return output.str();
}

int main(int argc, char *argv[]) {
    locale::global(locale(""));
    if (argc == 2) {
        std::wcout << Ascii2Hex(argv[1]) << std::endl;
    }
    return 0;
}

