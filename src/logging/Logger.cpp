#include "Logger.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <filesystem>

Logger::Logger(
    const std::string& filePath
){
    std::filesystem::path path(filePath);

    if (!path.parent_path().empty()) {
        std::filesystem::create_directories(
            path.parent_path()
        );
    }

    logFile.open(
        filePath,
        std::ios::app
    );
    if (!logFile.is_open()) {
        std::cerr
            << "Failed to open log file: "
            << filePath
            << '\n';
    }

}
Logger::~Logger(){
    if(logFile.is_open()){
        logFile.close();
    }
}
void Logger::log(
    LogLevel level,
    const std::string& message
)
{
    std::lock_guard<std::mutex> lock(logMutex);

    const auto now =
        std::chrono::system_clock::now();

    const std::time_t time =
        std::chrono::system_clock::to_time_t(now);

    std::tm localTime{};

#ifdef _WIN32
    localtime_s(&localTime, &time);
#else
    localtime_r(&time, &localTime);
#endif

    std::ostringstream output;

    output
        << '['
        << std::put_time(
               &localTime,
               "%Y-%m-%d %H:%M:%S"
           )
        << "] "
        << levelToString(level)
        << " "
        << message;

    const std::string logMessage = output.str();

    // Console
    std::cout << logMessage << '\n';

    // File
    if (logFile.is_open()) {
        logFile << logMessage << '\n';
        logFile.flush();
    }
}

std::string Logger::levelToString(
    LogLevel level
) const
{
    switch (level) {

    case LogLevel::INFO:
        return "INFO ";

    case LogLevel::WARNING:
        return "WARN ";

    case LogLevel::ERROR:
        return "ERROR";
    }

    return "UNKNOWN";
}