//
// Created by l30014168 on 2022/6/30.
//
#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>

int main(int argc, char *argv[]) {
    uint64_t ram_size;
    char *end;
    if (argc == 2) {
        ram_size = strtol(argv[1], &end, 10);
    } else {
        std::cout << "param num must = 1, cur = " << argc - 1 << std::endl;
        return 0;
    }
    char *buf = (char *) malloc(sizeof(char) * ram_size * 1024 * 1024);
    if (buf == nullptr) {
        std::cout << "malloc failed!" << std::endl;
    }
    for (uint64_t  idx = 0; idx < ram_size * 1024 * 1024; idx++) {
        buf[idx] = rand() % UINT8_MAX;
    }
    std::cout << "alloc " << ram_size << "M ram" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(120));
    free(buf);  // 释放内存空间
    return 0;
}
