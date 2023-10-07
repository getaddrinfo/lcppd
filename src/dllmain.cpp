#include "core/ivsdk.h"
#include "core/common.h"

#include "stations/station.cpp"
#include "stations/stations.cpp"
#include "vehicle/vehicle.cpp"

auto logr = CScopedLogger::create("main");
auto stationManager = new CStationMgr();

#define RENDER_STATIONS_JOB_MUST_REACH 200
static int renderStationsJobFrameCounter = RENDER_STATIONS_JOB_MUST_REACH;
static int* htmlViewportHandle;

static CDutyVehicle* dutyVehicle = nil;

void onLoad()
{
    CLogger::setLevel(ELL_DEBUG);
    logr->info("loaded");
};

void onProcessScriptsEvent()
{
    if (renderStationsJobFrameCounter == RENDER_STATIONS_JOB_MUST_REACH) {
        stationManager->render();
        renderStationsJobFrameCounter = 0;
    }

    renderStationsJobFrameCounter++;

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