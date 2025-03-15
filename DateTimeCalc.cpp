#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>


std::chrono::seconds GetTimeDuration(const std::string &durationStr) {
    std::istringstream ss(durationStr);
    int hours, minutes, seconds;
    char colon1, colon2; // 用于跳过冒号
    ss >> hours >> colon1 >> minutes >> colon2 >> seconds;

    if (ss.fail() or colon1 != ':' or colon2 != ':' or hours < 0 or minutes < 0 or seconds < 0) {
        throw std::invalid_argument("duration format error");
    }

    return std::chrono::hours(hours) + std::chrono::minutes(minutes) + std::chrono::seconds(seconds);
}

std::string DateTimeCalc(const std::string &anchorTimeStr, const std::string &dateTimeOp, const std::string &durationStr) {
    if (dateTimeOp != "+" and dateTimeOp != "-") {
        throw std::invalid_argument("operation format error");
    }
    std::stringstream ss;
    std::tm tm = {};
    ss << anchorTimeStr;
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    ss.str("");
    ss.clear();
    // 将std::tm转换为time_point
    auto anchorTime = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    auto duration = GetTimeDuration(durationStr);
    std::time_t finalTime = std::chrono::system_clock::to_time_t(dateTimeOp == "+" ? anchorTime + duration : anchorTime - duration);
    ss << std::put_time(std::localtime(&finalTime), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}


// 用于 wasm
#ifdef WASM_EMCC
#include <emscripten.h>
extern "C" {
    EMSCRIPTEN_KEEPALIVE
    const char* C_DateTimeCalc(const char *anchorTimeStr, const char *dateTimeOp, const char *durationStr) {
        auto finalTime = DateTimeCalc(anchorTimeStr, dateTimeOp, durationStr);
        return strdup(finalTime.c_str());
    }
}
#else
int main(int argc, char *argv[]) {
    if (argc == 4) {
        std::string anchorTimeStr = argv[1];
        std::string opStr = argv[2];
        std::string durationStr = argv[3];
        
        auto finalTime = DateTimeCalc(anchorTimeStr, opStr, durationStr);
        std::cout << anchorTimeStr << " " << opStr << " " << durationStr << " = " << finalTime << std::endl;
    }
    return 0;
}
#endif