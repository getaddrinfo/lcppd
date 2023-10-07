#include "calloutmgr.h"
#include "core/scopedlogger.h"

CScopedLogger* CCalloutMgr::g_log = CScopedLogger::create("CalloutManager");

std::vector<ICallout*> CCalloutMgr::m_registeredCallouts;
ICallout* CCalloutMgr::m_currentlyActiveCallout = nil;

void CCalloutMgr::add(ICallout* callout) {
    m_registeredCallouts.push_back(callout);
}

// TODO: is this an appropriate random sourcing for callouts?
ICallout* CCalloutMgr::random() {
    auto front = m_registeredCallouts.begin();
    std::advance(front, std::rand() % m_registeredCallouts.size());

    return *front;
}

ICallout* CCalloutMgr::active() {
    return m_currentlyActiveCallout;
}

CCalloutMgr::~CCalloutMgr() {
    g_log->trace("releaing callouts");

    // we know we keep a reference to the callout in 
    // m_registeredCallouts as well...
    if (m_currentlyActiveCallout != nil) {
        m_currentlyActiveCallout = nil;
    }

    // cleanup pointers to registered callouts...
    for(auto callout: m_registeredCallouts) {
        delete callout;
    }

    g_log->trace("released ...");
}