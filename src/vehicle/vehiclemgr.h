#ifndef _VEHICLE_MGR_H
#define _VEHICLE_MGR_H

#include <string>

class CVehicleMgr
{
public:
    static std::string g_possibleVehicles[7];
    
    bool m_bIsPickingVehicle;
    void onTick();

    CVehicleMgr();
    ~CVehicleMgr();
};

#endif _VEHICLE_MGR_H
