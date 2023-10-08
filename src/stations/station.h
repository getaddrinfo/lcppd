#ifndef _STATION_H
#define _STATION_H

#include "core/ivsdk.h"
#include "core/common.h"

#include "core/scopedlogger.h"

#define ENTRANCE_RADIUS 1.5

struct Vector
{
    float x, y, z;
};

class CStation
{
public:
    static CScopedLogger* ms_pLogger;

    CVector* m_pBlipVector;
    CVector* m_pCarChooseVector;
    float m_fCarChooseHeading;
    
    bool m_bHasBlip;
    bool m_bHasCheckpoint;

    Scripting::Blip m_nBlipHandle;
    int m_nCheckpointHandle;


    CStation(Vector blip, Vector choose, float heading);
    ~CStation();

    // control rendering
    void show();
    void hide();

    // true if we are standing in the checkpoit
    // of this station (2d), false otherwise 
    bool inCheckpointBounds();

    // do rendering work each tick
    void render();

    void _placeBlip();
    void _removeBlip();

    void _drawCheckpoint();

    void _placeEntrance();
    void _removeEntrance();
};

#endif _STATION_H