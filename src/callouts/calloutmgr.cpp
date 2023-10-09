#include "calloutmgr.h"
#include "core/scopedlogger.h"

CScopedLogger* CCalloutMgr::ms_pLogger = CScopedLogger::create("CalloutManager");

CCalloutMgr::CCalloutMgr() {
    m_vRegisteredCallouts = {};
    m_pCurrentlyActiveCallout = nil;
}

void CCalloutMgr::add(ICallout* callout) {
    m_vRegisteredCallouts.push_back(callout);
}

// TODO: is this an appropriate random sourcing for callouts?
ICallout* CCalloutMgr::random() {
    auto front = m_vRegisteredCallouts.begin();
    std::advance(front, std::rand() % m_vRegisteredCallouts.size());

    return *front;
}

ICallout* CCalloutMgr::active() {
    return m_pCurrentlyActiveCallout;
}

CCalloutMgr::~CCalloutMgr() {
    ms_pLogger->trace("releaing callouts");

    // we know we keep a reference to the callout in 
    // m_vRegisteredCallouts as well...
    if (m_pCurrentlyActiveCallout != nil) {
        m_pCurrentlyActiveCallout = nil;
    }

    // cleanup pointers to registered callouts...
    for(auto callout: m_vRegisteredCallouts) {
        delete callout;
    }

    ms_pLogger->trace("released ...");
}