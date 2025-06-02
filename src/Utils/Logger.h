#pragma once

#include <string>
#include <fstream>
#include <mutex>
//#include <iostream>

namespace pine {

enum class LogLevel {
	INF, // Information
    SUC, // Success
    MSC, // Misc
	WAR, // Warning
	ERR  // Error
};

class Logger {
public:
    static Logger& Instance();

    void SetLogFile(const std::string& filename);
    void Log(const std::string& message, LogLevel level = LogLevel::INF);

    // Convenience methods
    void Info(const std::string& message);
    void Success(const std::string& message);
    void Misc(const std::string& message);
    void Warning(const std::string& message);
    void Error(const std::string& message);

private:
    Logger();
    ~Logger();
    //Logger(const Logger&) = delete;
    //Logger& operator=(const Logger&) = delete;

    std::ofstream _file;
    std::mutex _mutex;
    bool _fileOpen = false;

    std::string LevelToString(LogLevel level);

    // Color helpers
    void SetConsoleColor(LogLevel level);
    void ResetConsoleColor();
};

} 