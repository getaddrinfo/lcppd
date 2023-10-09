#include "core/ivsdk.h"
#include "core/common.h"

#include "callouts/calloutmgr.cpp"

#include "stations/interiormgr.cpp"
#include "stations/station.cpp"
#include "stations/stationmgr.cpp"

#include "vehicle/vehicle.cpp"

CScopedLogger* logr = CScopedLogger::create("dllmain");

CStationMgr* stationManager = new CStationMgr();
CCalloutMgr* calloutManager = new CCalloutMgr();

void onLoad()
{
    CLogger::init();
    CLogger::setLevel(LOG_LEVEL_DEBUG);
    logr->info("loaded");
};

void onProcessScriptsEvent()
{
    // unload
    if (Scripting::IS_KEYBOARD_KEY_PRESSED(KEY_RIGHT_ALT) && Scripting::IS_KEYBOARD_KEY_JUST_PRESSED(KEY_BACKSPACE))
    {
        logr->warn("reloading ...");
        reload();
        logr->info("reloaded");
        return;
    }

    stationManager->onTick();
};

void reload()
{
    // dealloc
    delete stationManager;
    delete calloutManager;

    // reassign
    stationManager = new CStationMgr();
    calloutManager = new CCalloutMgr();
}

void plugin::gameStartupEvent() 
{
    plugin::gameLoadEvent::Add(onLoad);
    plugin::processScriptsEvent::Add(onProcessScriptsEvent);
};