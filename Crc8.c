#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint8_t crc8(const uint8_t *data, const size_t length) {
    uint8_t crc = 0;
    uint8_t poly = 0x07;    // 多项式 x^8 + x^2 + x^1 + 1
    for (size_t idx = 0; idx < length; ++idx) {
        crc ^= data[idx];
        for (uint8_t n = 0; n < 8; ++n) {
            if (crc & 0x80) {
                crc = (crc << 1) ^ poly;
            } else {
                crc <<= 1;
            }
        }
    }
    return crc;
}

int main(int argc, char *argv[]) {
    FILE *file = fopen(argv[1], "rb");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // 获取文件长度
    fseek(file, 0, SEEK_END);
    long file_length = ftell(file);
    fseek(file, 0, SEEK_SET);


    // 分配足够的内存来存储文件内容
    uint8_t *buffer = (uint8_t *)malloc(file_length);
    if (buffer == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return 1;
    }

    // 读取文件内容到缓冲区
    if (fread(buffer, 1, file_length, file) != file_length) {
        perror("Error reading file");
        free(buffer);
        fclose(file);
        return 1;
    }

    uint8_t crc8_val = crc8(buffer, file_length);
    printf("crc8: 0x%02x\n", crc8_val);
    free(buffer);
    fclose(file);
    return 0;
}

