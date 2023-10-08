#ifndef _SCOPED_LOGGER_H
#define _SCOPED_LOGGER_H

#include <string>
#include "logger.h"

using std::string;

class CScopedLogger
{
private:
    // We keep this private so they have to use CScopedLogger::create
    CScopedLogger(const std::string scope) {
        m_sScope = scope;
        m_bHasLevelOverride = false;
    }
    
    CScopedLogger(const std::string scope, eLogLevel override) {
        m_sScope = scope;
        m_bHasLevelOverride = true;
        m_eLevelOverride = override;
    }

    inline void log(eLogLevel level, string msg) {
        if (!isEnabled(level)) return;

        CLogger::write(level, m_sScope, msg);
    }

public:
    std::string m_sScope;
    eLogLevel m_eLevelOverride;
    bool m_bHasLevelOverride;

    bool isEnabled(eLogLevel level) {
        if (m_bHasLevelOverride) {
            return level >= m_eLevelOverride;
        }

        return CLogger::isEnabled(level);
    }


    static CScopedLogger* create(const std::string scope) {
        return new CScopedLogger(scope);
    }

    static CScopedLogger* create(const std::string scope, eLogLevel override) {
        return new CScopedLogger(scope, override);
    }

    void trace(string msg) {
        log(LOG_LEVEL_TRACE, msg);
    };

    void debug(string msg) {
        log(LOG_LEVEL_DEBUG, msg);
    };

    void info(string msg) {
        log(LOG_LEVEL_INFO, msg);
    };

    void warn(string msg) {
        log(LOG_LEVEL_WARN, msg);
    };
    
    void error(string msg) {
        log(LOG_LEVEL_ERROR, msg);
    };
};

#endif _SCOPED_LOGGER_H