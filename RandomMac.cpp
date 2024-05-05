#include <iostream>
#include <random>
#include <sstream>
#include <iomanip>

std::string generateRandomMacAddress() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0x00, 0xFF);

    std::stringstream mac;
    mac << std::hex << std::uppercase << std::setfill('0');
    for (int i = 0; i < 6; ++i) {
        mac << std::setw(2) << dis(gen);
        if (i < 5) {
            mac << ":";
        }
    }

    return mac.str();
}

int main() {
    const std::string randomMac = generateRandomMacAddress();
    std::cout << randomMac << std::endl;
    return 0;
}
