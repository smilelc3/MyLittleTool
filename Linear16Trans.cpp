#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cstdint>

// 位操作
#define getBit(n, idx) ((n) >> (idx) & 1)           // 获取某一位值
#define bitMask(n)  ((1ULL << (n)) - 1)


// Linear16 mantissa ∈ [0, 65535] ， exp ∈ [-16, 15]， ans = mantissa * 2^(exp); 高5bit为exp, 低11bit为 mantissa，均为补码
// 可以表示值范围为：[0, 0x7FFF8000]
double Linear16ToDouble(uint8_t exp, uint16_t man) {
    double ans; // ans = mantissa * 2^(exp); 高5bit为exp(补码), 低11bit为 mantissa(无符号)
    exp = exp & bitMask(5);
    /* 指数为负 */
    if (getBit(exp, 4) == 1) {
        exp = (~(exp - 1)) & bitMask(4);
        ans = man;
        while (exp > 0) {
            exp--;
            ans /= 2;
        }
    } else {
        ans = static_cast<uint32_t>(man) << exp;
    }
    return ans;
}

// 用于 wasm
#ifdef WASM_EMCC
#include <emscripten.h>
extern "C" {
    EMSCRIPTEN_KEEPALIVE
    const char* C_Linear16Trans(const char *expStr, const char *manStr) {
        auto exp = std::stoul(expStr, nullptr, 0);
        auto man = std::stoul(manStr, nullptr, 0);
        std::ostringstream output;
        output << std::setprecision(4) << Linear16ToDouble(static_cast<uint8_t>(exp), static_cast<uint16_t>(man));
        return strdup(output.str().c_str());
    }
}
#else
int main(int argc, char *argv[]) {
    if (argc == 3) {
        std::string linear16ExpStr = argv[1];
        std::string linear16ManStr = argv[2];
        auto exp = std::stoul(linear16ExpStr, nullptr, 0);
        auto val = std::stoul(linear16ManStr, nullptr, 0);
        std::cout << std::setprecision(4) << Linear16ToDouble(exp, val) << std::endl;
    }
    return 0;
}
#endif