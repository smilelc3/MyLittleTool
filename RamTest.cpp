//
// Created by l30014168 on 2022/6/30.
//
#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <random>

int main(int argc, char *argv[]) {

    double ram_size_m;
    if (argc == 2) {
        ram_size_m = strtod(argv[1], nullptr);
    } else {
        std::cout << "param num must = 1, cur = " << argc - 1 << std::endl;
        return 0;
    }
    char *buf = (char *) malloc(sizeof(char) * static_cast<size_t>(ram_size_m * 1024 * 1024));
    if (buf == nullptr) {
        std::cout << "malloc failed!" << std::endl;
    }
    for (uint64_t idx = 0; idx < static_cast<size_t>(ram_size_m * 1024 * 1024); idx++) {
        buf[idx] = rand() % UINT8_MAX;
    }
    std::cout << "alloc " << ram_size_m << "M ram" << std::endl;

    std::random_device rd;  //如果可用的话，从一个随机数发生器上获得一个真正的随机数
    std::mt19937 gen(rd()); //gen是一个使用rd()作种子初始化的标准梅森旋转算法的随机数发生器
    std::uniform_int_distribution<> distrib(0, std::floor(ram_size_m - 1));
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        auto addr = distrib(gen);
        std::cout << "modify " << addr << "addr 1M ram" << std::endl;
        for (uint64_t idx = 0; idx < 1024 * 1024; idx++) {
            buf[addr + idx] = rand() % UINT8_MAX;
        }
    }

    free(buf);  // 释放内存空间
    return 0;
}
