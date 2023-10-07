#ifndef _STATION_H
#define _STATION_H

#include "core/ivsdk.h"
#include "core/common.h"

#include "core/scopedlogger.h"

struct Vector
{
    float x, y, z;
};

class CStation
{
public:
    static CScopedLogger* g_log;

    CVector* m_pBlipVector;
    CVector* m_pCarChooseVector;
    float m_fCarChooseHeading;
    
    bool m_bHasPlacedBlip;
    Scripting::Blip m_mapBlipHandle;
    Scripting::Blip m_groundBlipHandle;


    CStation(Vector blip, Vector choose, float heading);
    ~CStation();

    void placeBlip();
    void removeBlip();

    void placeEntrance();
    void removeEntrance();
};

#endif _STATION_H