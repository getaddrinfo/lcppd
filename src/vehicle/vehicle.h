#ifndef _VEHICLE_H
#define _VEHICLE_H

#include "core/common.h"
#include "core/scopedlogger.h"
#include "core/ivsdk.h"
#include <string>

class CDutyVehicle
{
public:
    static CScopedLogger* g_log;

    Scripting::Vehicle m_vehicleHandle;
    Scripting::Blip m_blipHandle;
    std::string m_sModelName;

    bool m_bIsUnreapable;
    bool m_bHasBlip;

    CDutyVehicle(Scripting::Vehicle handle);
    CDutyVehicle(std::string model);
    ~CDutyVehicle();

    void addBlip();
    void removeBlip();

    void markUnreapable();
    void markReapable();
};



#endif