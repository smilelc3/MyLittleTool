#include <iostream>
#include <sstream>
#include <iomanip>

std::string Ascii2Hex(const std::string &input) {
    std::ostringstream output;
    for (const auto &ch: input) {
        output << "0x" << std::setfill('0') << std::setw(2) << std::hex << static_cast<unsigned short>(ch) << " ";
    }
    return output.str();
}

// 用于 wasm
#ifdef WASM_EMCC
#include <emscripten.h>
extern "C" {
    EMSCRIPTEN_KEEPALIVE
    const char* C_Ascii2Hex(const char *input) {
        auto str = Ascii2Hex(input);
        return strdup(str.c_str());
    }
}
#else
int main(int argc, char *argv[]) {
    if (argc == 2) {
        std::cout << Ascii2Hex(argv[1]) << std::endl;
    }
    return 0;
}
#endif