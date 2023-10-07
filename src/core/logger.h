#ifndef _LOGGER_H
#define _LOGGER_H

#include <string>
using std::string;

enum eLogLevel
{
    ELL_TRACE,
    ELL_DEBUG,
    ELL_INFO,
    ELL_WARN,
    ELL_ERROR
};

class CLogger
{
private:
    static eLogLevel currentLevel;
    static std::string levels[5];

    static void log(eLogLevel level, string source, string e);

public:
    static bool isEnabled(eLogLevel level);
    
    static void trace(string source, string msg);
    static void debug(string source, string msg);
    static void info(string source, string msg);
    static void warn(string source, string msg);
    static void error(string source, string msg);
    static void setLevel(eLogLevel newLevel);
};

#endif _LOGGER_H