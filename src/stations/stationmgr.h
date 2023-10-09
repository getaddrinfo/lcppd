#ifndef _STATIONS_MGR_H
#define _STATIONS_MGR_H

#include "station.h"
#include "interiormgr.h"
#include "core/scopedlogger.h"

#define MAX_NUM_BLIPS 3
#define NUM_FRAMES_FOR_MAP_RECALC 200

class CStationMgr
{
    static CScopedLogger* ms_pLogger;
    static bool m_bShowAllBlips;
    
    int m_nFrames;
    CInteriorMgr* m_pInterior;

    CStation* g_stations[15] = {
        new CStation(Vector{93.5, 1212.0, 13.74}, Vector{84.0, 1240.0, 14.5}, 90),
        new CStation(Vector{48.0, 680.0, 13.5}, Vector{54.0, 668.0, 13.5}, 90),
        new CStation(Vector{212.11, -207.99, 9.76}, Vector{266.75, -212.06, 5.56}, 180),
        new CStation(Vector{992.0, 1876.0, 22.8}, Vector{997.0, 1885.0, 22.8}, 90),
        new CStation(Vector{-407.0, 281.0, 12.0}, Vector{-422.0, 284.0, 10.0}, 180),
        new CStation(Vector{435.0, 1595.0, 15.3}, Vector{443.0, 1595.0, 15.3}, 90),
        new CStation(Vector{899.0, -355.0, 16.5}, Vector{891.0, -388.0, 15.8}, 90),
        new CStation(Vector{1235.0, 576.0, 37.5}, Vector{1246.0, 577.0, 37.5}, 90),
        new CStation(Vector{-928.0, 1296.0, 23.5}, Vector{-880.0, 1307.0, 20.5}, 90),
        new CStation(Vector{-417.0, 1102.0, 10.5}, Vector{-418.0, 1098.0, 10.5}, 90),
        new CStation(Vector{-1224.0, -234.0, 1.5}, Vector{-1233.0, -288.0, 2.0}, 0),
        new CStation(Vector{2170.0, 449.0, 5.2}, Vector{2161.0, 406.0, 4.8}, 270),
        new CStation(Vector{-382.0, -265.0, 11.0}, Vector{-401.0, -270.0, 11.5}, 90),
        new CStation(Vector{-1717.05, 277.17, 21.0}, Vector{-1737.60, 271.11, 21.75}, 90),
        new CStation(Vector{1231.56, -88.98, 27.0}, Vector{1209.28, -101.44, 27.0}, 180)
    };


public:
    CStationMgr();
    ~CStationMgr();
    
    void onTick();

    void drawMapBlips();
    void drawCheckpoints();


    void showAllBlips();
    void showNearbyBlips();

};

#endif _STATIONS_MGR_H