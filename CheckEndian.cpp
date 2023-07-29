//
// Created by l30014168 on 2022/7/11.
//

#include <iostream>

bool isLittleEndian() {
    union check {
        int i;
        char c;
    } endian{};
    endian.i = 1;
    return endian.c == 1;
}


int main(int argc, char *argv[]) {
    std::cout << "CPU is " << (isLittleEndian() ? "little" : "big") << " endian" << std::endl;
    return 0;
}

