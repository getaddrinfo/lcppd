#include "logger.h"

// TODO: move to configuration files
#define IS_DEVELOPMENT

eLogLevel CLogger::ms_currentLevel = LOG_LEVEL_INFO;

std::string CLogger::ms_levels[5] = {
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

void CLogger::init() {
    #ifdef IS_DEVELOPMENT
        AllocConsole();
        freopen("CON", "w", stdout);
        freopen("CON", "w", stderr);
        freopen("CON", "r", stdin);
    #endif
}

bool CLogger::isEnabled(eLogLevel level) {
    return level >= CLogger::ms_currentLevel;
}

void CLogger::trace(
    string source, string msg
) {
    CLogger::log(LOG_LEVEL_TRACE, source, msg);
}

void CLogger::debug(
    string source, string msg
) {
    CLogger::log(LOG_LEVEL_DEBUG, source, msg);
}

void CLogger::info(
    string source, string msg
) {
    CLogger::log(LOG_LEVEL_INFO, source, msg);
}

void CLogger::warn(
    string source, string msg
) {
    CLogger::log(LOG_LEVEL_WARN, source, msg);
}

void CLogger::error(
    string source, string msg
) {
    CLogger::log(LOG_LEVEL_ERROR, source, msg);
}

void CLogger::log(eLogLevel level, std::string source, std::string e) {
    if (!CLogger::isEnabled(level)) {
        return;
    }

    return write(level, source, e);
}

void CLogger::write(eLogLevel level, std::string source, string e ) {
    string now = _getCurrentDateTime();
    
    std::string levelName = ms_levels[level];
    int padding = 5 - levelName.length();

    std::cout << now << " " << ms_levels[level];

    if(padding > 0) {
        while(padding--) { std::cout << " "; }
    }

    std::cout << "[" << source << "]: " << e << "\n";
}

void CLogger::setLevel(eLogLevel newLevel) {
    CLogger::ms_currentLevel = newLevel;
}