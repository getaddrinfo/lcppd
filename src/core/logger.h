#ifndef _LOGGER_H
#define _LOGGER_H

#include <iostream>
#include <string>
#include <windows.h>

using std::string;

enum eLogLevel
{
    LOG_LEVEL_TRACE,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR
};

class CLogger
{
public:
    static eLogLevel ms_currentLevel;
    static std::string ms_levels[5];

    static void log(eLogLevel level, string source, string e); // checks if level is enabled
    static void write(eLogLevel level, string source, string e); // writes irregardless of level availability
    static bool isEnabled(eLogLevel level);
    
    static void trace(string source, string msg);
    static void debug(string source, string msg);
    static void info(string source, string msg);
    static void warn(string source, string msg);
    static void error(string source, string msg);
    static void setLevel(eLogLevel newLevel);
    
    static void init();
};

#endif _LOGGER_H