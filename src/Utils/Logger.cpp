#include "Utils/Logger.h"
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

namespace pine {

Logger& Logger::Instance() {
    static Logger instance;
    return instance;
}

Logger::Logger() = default;

Logger::~Logger() {
    if (_fileOpen) {
        _file.close();
    }
}

void Logger::SetLogFile(const std::string& filename) {
    std::lock_guard<std::mutex> lock(_mutex);
    if (_fileOpen) {
        _file.close();
    }
    _file.open(filename, std::ios::out | std::ios::app);
    _fileOpen = _file.is_open();
}

void Logger::SetConsoleColor(LogLevel level) {
#ifdef _WIN32
    const HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE);
    WORD color = 0x07; // Default: white/gray
    switch (level) {
        case LogLevel::INF: color = 0x07; break; // White/gray
        case LogLevel::WAR: color = 0x0E; break; // Yellow
        case LogLevel::ERR: color = 0x0C; break; // Red
    }
    SetConsoleTextAttribute(h_console, color);
#else
    switch (level) {
        case LogLevel::Info:    std::cout << "\033[0m"; break; // Reset/white
        case LogLevel::Warning: std::cout << "\033[33m"; break; // Yellow
        case LogLevel::Error:   std::cout << "\033[31m"; break; // Red
    }
#endif
}

void Logger::ResetConsoleColor() {
#ifdef _WIN32
    const HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h_console, 0x07); // Default: white/gray
#else
    std::cout << "\033[0m";
#endif
}

void Logger::Log(const std::string& message, const LogLevel level) {
    std::lock_guard<std::mutex> lock(_mutex);
    const std::string output = "[" + LevelToString(level) + "] " + message;

    // Print to console with color
    SetConsoleColor(level);
    std::cout << output << '\n';
    ResetConsoleColor();

    // Print to file if open (no color codes)
    if (_fileOpen) {
        _file << output << '\n';
    }
}

void Logger::Info(const std::string& message) {
    Log(message, LogLevel::INF);
}

void Logger::Warning(const std::string& message) {
    Log(message, LogLevel::WAR);
}

void Logger::Error(const std::string& message) {
    Log(message, LogLevel::ERR);
}

std::string Logger::LevelToString(const LogLevel level) {
    switch (level) {
        case LogLevel::INF: return "INFO";
        case LogLevel::WAR: return "WARNING";
        case LogLevel::ERR: return "ERROR";
        default: return "UNKNOWN";
    }
}

} // namespace pine