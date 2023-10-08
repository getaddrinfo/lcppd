#include "core/ivsdk.h"
#include "core/common.h"

#include "stations/station.cpp"
#include "stations/stationmgr.cpp"

#include "vehicle/vehicle.cpp"

auto logr = CScopedLogger::create("dllmain");
auto stationManager = new CStationMgr();

static CDutyVehicle* dutyVehicle = nil;

void onLoad()
{
    CLogger::init();
    CLogger::setLevel(LOG_LEVEL_DEBUG);
    logr->info("loaded");
};

void onProcessScriptsEvent()
{
    stationManager->onTick();

    if (Scripting::IS_GAME_KEYBOARD_KEY_JUST_PRESSED(KEY_PERIOD))
    {
        if(dutyVehicle != nil) {
            logr->warn("duty vehicle already registered");
            return;
        }

        logr->debug("KEY_PERIOD pressed - spawning noose via scripting api");
        
        dutyVehicle = new CDutyVehicle("noose");

        std::ostringstream stream;
        stream << "spawned noose (veh = " << dutyVehicle->m_vehicleHandle << ", blip = " << dutyVehicle->m_blipHandle << ") " << dutyVehicle;
        logr->debug(stream.str());
    }
};

void plugin::gameStartupEvent() 
{
    plugin::gameLoadEvent::Add(onLoad);
    plugin::processScriptsEvent::Add(onProcessScriptsEvent);
};