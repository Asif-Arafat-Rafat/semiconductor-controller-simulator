#pragma once

#include <fstream>
#include <mutex>
#include <string>

enum class LogLevel {
    INFO,
    WARNING,
    ERROR
};

class Logger {
public:
    explicit Logger(
        const std::string& filePath
    );

    ~Logger();

    void log(
        LogLevel level,
        const std::string& message
    );

private:
    std::mutex logMutex;
    std::ofstream logFile;
    std::string levelToString(
        LogLevel level
    ) const;
};