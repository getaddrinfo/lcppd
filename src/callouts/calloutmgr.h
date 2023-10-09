#ifndef _CALLOUT_MGR_H
#define _CALLOUT_MGR_H

#include <vector>

#include "core/common.h"
#include "core/scopedlogger.h"
#include "callout.h"

class CCalloutMgr
{
public:
    static CScopedLogger* ms_pLogger;

    std::vector<ICallout*> m_vRegisteredCallouts;
    ICallout* m_pCurrentlyActiveCallout;


    void add(ICallout *callout);
    ICallout* random();
    ICallout* active();

    CCalloutMgr();
    ~CCalloutMgr();
};

#endif _CALLOUT_MGR_H