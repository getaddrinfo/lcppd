#include "logger.h"


// TODO: move to configuration files
#define LOG_OUTPUT_DIRECTORY ""

#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>

eLogLevel CLogger::currentLevel = ELL_INFO;

std::string CLogger::levels[5] = {
    "TRACE",
    "DEBUG",
    "INFO",
    "WARN",
    "ERROR"
};

inline string _getCurrentDateTime(){
    time_t now = time(0);
    struct tm  tstruct;
    char  buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    return string(buf);
};


bool CLogger::isEnabled(eLogLevel level) {
    return level >= CLogger::currentLevel;
}

void CLogger::trace(
    string source, string msg
) {
    CLogger::log(ELL_TRACE, source, msg);
}

void CLogger::debug(
    string source, string msg
) {
    CLogger::log(ELL_DEBUG, source, msg);
}

void CLogger::info(
    string source, string msg
) {
    CLogger::log(ELL_INFO, source, msg);
}

void CLogger::warn(
    string source, string msg
) {
    CLogger::log(ELL_WARN, source, msg);
}

void CLogger::error(
    string source, string msg
) {
    CLogger::log(ELL_ERROR, source, msg);
}

void CLogger::log(eLogLevel level, std::string source, std::string e) {
    if (!CLogger::isEnabled(level)) {
        return;
    }

    std::ostringstream stream("");
    string now = _getCurrentDateTime();
    
    std::string levelName = levels[level];
    int padding = 5 - levelName.length();


    stream << now << " " << levels[level];

    if(padding > 0) {
        while(padding--) { stream << " "; }
    }

    stream << " [" << source << "]: " << e << "\n";

    const std::string path = LOG_OUTPUT_DIRECTORY;

    // TODO: can we keep an open file handler and just append and flush?
    std::ofstream ofs(path.c_str(), std::ios_base::out | std::ios_base::app );
    ofs << stream.str().c_str();
    ofs.close();
}

void CLogger::setLevel(eLogLevel newLevel) {
    CLogger::currentLevel = newLevel;
}