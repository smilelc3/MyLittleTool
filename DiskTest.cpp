
#include <fstream>
#include <iostream>
#include <string>
#include <cstdint>

// xorshift 快速随机数生成器
class XorShift32RandomGenerator {
private:
    uint32_t r;
public:
    explicit XorShift32RandomGenerator(uint32_t seed) {
        this->r = seed;
    }

    uint32_t next() {
        r ^= r << 13;
        r ^= r >> 17;
        r ^= r << 5;
        return r;
    }
};

void DiskTest(std::string &filePath, int valMSize) {
    auto gen = XorShift32RandomGenerator(time(nullptr));
    uint32_t dataSizeByte = 0;
    const uint32_t targetSizeByte = valMSize * 1024 * 1024; // 1G

    std::ofstream ofs;
    ofs.open(filePath, std::ios::ate | std::ios::binary);
    while (dataSizeByte < targetSizeByte) {
        auto t = gen.next();
        ofs.write(reinterpret_cast<const char *>(&t), sizeof(t));
        dataSizeByte += sizeof(t);
        // 每1M进行一次 刷写到硬盘
        if ((dataSizeByte & 0xFFFFF) == 0) {
            ofs.flush();
            std::cout << "write " << (dataSizeByte >> 20) << "M" << std::endl;
        }
    }

    ofs.close();
}

int main(int argc, char *argv[]) {
    if (argc == 3) {
        std::string filePath = argv[1];
        auto valMSize = std::stoi(std::string(argv[2]));
        DiskTest(filePath, valMSize);
    }
    return 0;
}