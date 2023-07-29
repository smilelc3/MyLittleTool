#include <iostream>
#include <iomanip>
#include <string>
// 位操作
#define getBit(n, idx) ((n) >> (idx) & 1)           // 获取某一位值
#define bitMask(n)  ((1ULL << (n)) - 1)

// Linear11 mantissa ∈ [-1024, 1023] ， exp ∈ [-16, 15]， ans = mantissa * 2^(exp); 高5bit为exp, 低11bit为 mantissa，均为补码
// 可以表示值范围为：[-2^25, 0x4000000]
double Linear11ToDouble(uint16_t word) {
    double ans;
    bool isManNeg = false; // 记录基数是否为负数

    /* 按照 Linear 11 格式进行转换 */
    uint8_t exp = word >> 11;
    uint16_t man = word & bitMask(11);
    /* 底数为负 */
    if (getBit(man, 10) == 1) {
        man = (~(man - 1)) & bitMask(10);
        isManNeg = true;
    }
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
    return isManNeg ? -ans : ans;
}

int main(int argc, char *argv[]) {
    if (argc == 2) {
        std::string linear11Str = argv[1];
        auto val = std::stoul(linear11Str, nullptr, 0);
        std::cout << std::setprecision(3) << Linear11ToDouble(val) << std::endl;
    }
    return 0;
}