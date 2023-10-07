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
    }
public:
    std::string m_sScope;

    static CScopedLogger* create(const std::string scope) {
        return new CScopedLogger(scope);
    }

    void trace(string msg) {
        CLogger::trace(m_sScope, msg);
    };
    void debug(string msg) {
        CLogger::debug(m_sScope, msg);
    };
    void info(string msg) {
        CLogger::info(m_sScope, msg);
    };
    void warn(string msg) {
        CLogger::warn(m_sScope, msg);
    };
    void error(string msg) {
        CLogger::error(m_sScope, msg);
    };
};

#endif _SCOPED_LOGGER_H