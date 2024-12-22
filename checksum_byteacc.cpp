#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <future>
#include <iomanip>
#include <numeric>


// 读取数据块的任务函数
std::vector<uint8_t> readBlock(const std::string &filename, std::streampos start, std::streampos end) {
    std::ifstream file(filename, std::ios::binary);
    if (file.fail()) {
        std::cerr << "unable to open file" << std::endl;
        return {};
    }
    // 定位到数据块开始处
    file.seekg(start);
    // 读取数据块
    std::vector<uint8_t> buffer(end - start);
    file.read(reinterpret_cast<char *>(buffer.data()), buffer.size());
    file.close();
    return buffer;
}

// 处理数据块的函数
inline uint32_t processBlock(const std::vector<uint8_t> &buffer) {
    return std::accumulate(buffer.begin(), buffer.end(), 0u);
}


int ByteAccByFile(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);
    if (file.fail()) {
        std::cerr << "unable open file" << std::endl;
        return -1;
    }
    // 获取文件大小
    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();
    file.close();
    std::cout << "file size: " << fileSize << " Bytes" << std::endl;

    auto nproc = std::thread::hardware_concurrency();

    std::cout << "proc num: " << nproc << std::endl;
    // 计算每个线程需要处理的数据块大小
    std::streampos blockSize = fileSize / nproc;

    // 创建并初始化每个线程的异步任务
    std::vector<std::future<std::vector<uint8_t> > > readTasks;
    std::vector<std::future<uint32_t> > processTasks;

    // 异步读取和处理每个数据块
    auto starTime = std::chrono::high_resolution_clock::now();
    for (auto i = 0; i < nproc; ++i) {
        std::streampos start = i * blockSize;
        std::streampos end = (i == nproc - 1) ? fileSize : start + blockSize;
        // 异步读取数据块
        readTasks.emplace_back(std::async(std::launch::async, readBlock, filename, start, end));
        // 异步处理数据块
        processTasks.emplace_back(std::async(std::launch::async, processBlock, readTasks.back().get()));
    }

    // 等待所有处理任务完成并获取结果
    std::vector<uint32_t> byteaccs;
    byteaccs.reserve(processTasks.size());
    for (auto &task: processTasks) {
        byteaccs.emplace_back(task.get());
    }
    auto endTime = std::chrono::high_resolution_clock::now();

    // 计算总的字节访问计数
    uint32_t totalByteAcc = std::accumulate(byteaccs.begin(), byteaccs.end(), 0u);
    std::cout << "byteacc: 0x" << std::hex << std::uppercase << std::setfill('0') << totalByteAcc
              << std::endl;
    std::cout << "cost time: " << static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(
            endTime - starTime).count()) / 1000 << "s" << std::endl;

    return 0;
}

// 用于 wasm
#ifdef WASM_EMCC
#include <emscripten.h>

extern "C" {
    EMSCRIPTEN_KEEPALIVE
    const char* C_ByteAccByMem(const char* buffer, uint32_t length) {
        uint32_t byteAcc = 0;
        for (uint32_t idx = 0; idx < length; ++idx) {
            byteAcc += buffer[idx];
        }
        std::stringstream output;
        output << "0x" << std::hex << std::uppercase << std::setw(8) << std::setfill('0') << byteAcc;
        return strdup(output.str().c_str());
    }
}
#else

int main(int argc, char *argv[]) {
    return ByteAccByFile(std::string(argv[1]));
}

#endif