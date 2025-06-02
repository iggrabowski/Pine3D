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
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    WORD color = 0x07; // Default: white/gray
    switch (level) {
        case LogLevel::INF: color = 0x07; break; // White/gray
        case LogLevel::SUC: color = 0x0A; break; // Bright green
        case LogLevel::MSC: color = 0x09; break; // Blue
        case LogLevel::WAR: color = 0x0E; break; // Yellow
        case LogLevel::ERR: color = 0x0C; break; // Red
    }
    SetConsoleTextAttribute(hConsole, color);
#else
    switch (level) {
        case LogLevel::INF: std::cout << "\033[0m"; break;      // Reset/white
        case LogLevel::SUC: std::cout << "\033[1;32m"; break;   // Bright green
        case LogLevel::MSC: std::cout << "\033[1;34m"; break;   // Blue
        case LogLevel::WAR: std::cout << "\033[33m"; break;     // Yellow
        case LogLevel::ERR: std::cout << "\033[31m"; break;     // Red
    }
#endif
}

void Logger::ResetConsoleColor() {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 0x07); // Default: white/gray
#else
    std::cout << "\033[0m";
#endif
}

void Logger::Log(const std::string& message, LogLevel level) {
    std::lock_guard<std::mutex> lock(_mutex);
    std::string output = "[ " + LevelToString(level) + " ] " + message;

    // Print to console with color
    SetConsoleColor(level);
    std::cout << output << std::endl;
    ResetConsoleColor();

    // Print to file if open (no color codes)
    if (_fileOpen) {
        _file << output << std::endl;
    }
}

void Logger::Info(const std::string& message) {
	if (!_fileOpen){
        // If the file is not open, set it to a default log file
        // This ensures that the log file is always set before logging
        Instance().SetLogFile("Log.txt");
		_fileOpen = true;
	}
    Log(message, LogLevel::INF);
}

void Logger::Success(const std::string& message) {
	if (!_fileOpen){
        // If the file is not open, set it to a default log file
        // This ensures that the log file is always set before logging
        Instance().SetLogFile("Log.txt");
		_fileOpen = true;
	}
    Log(message, LogLevel::SUC);
}

void Logger::Misc(const std::string& message)
{
	if (!_fileOpen){
        // If the file is not open, set it to a default log file
        // This ensures that the log file is always set before logging
        Instance().SetLogFile("Log.txt");
		_fileOpen = true;
	}
    Log(message, LogLevel::MSC);
}

void Logger::Warning(const std::string& message) {
	if (!_fileOpen){
        // If the file is not open, set it to a default log file
        // This ensures that the log file is always set before logging
        Instance().SetLogFile("Log.txt");
		_fileOpen = true;
	}
    Log(message, LogLevel::WAR);
}

void Logger::Error(const std::string& message) {
	if (!_fileOpen){
        // If the file is not open, set it to a default log file
        // This ensures that the log file is always set before logging
        Instance().SetLogFile("Log.txt");
		_fileOpen = true;
	}
    Log(message, LogLevel::ERR);
}

std::string Logger::LevelToString(LogLevel level) {
    switch (level) {
        case LogLevel::INF: return "INFO   ";
        case LogLevel::SUC: return "SUCCESS";
        case LogLevel::MSC: return "MISC   ";
        case LogLevel::WAR: return "WARNING";
        case LogLevel::ERR: return "ERROR  ";
        default: return "UNKNOWN";
    }
}

} // namespace pine