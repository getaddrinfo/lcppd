#ifndef _CALLOUT_MGR_H
#define _CALLOUT_MGR_H

#include <vector>

#include "core/common.h"
#include "core/scopedlogger.h"
#include "callout.h"

class CCalloutMgr
{
private:
    static std::vector<ICallout*> m_registeredCallouts;
    static ICallout* m_currentlyActiveCallout;

public:
    static CScopedLogger* g_log;

    static void add(ICallout *callout);
    static ICallout* random();
    static ICallout* active();

    ~CCalloutMgr();
};

#endif _CALLOUT_MGR_H