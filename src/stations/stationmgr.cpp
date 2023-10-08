#include "stationmgr.h"

#include <cmath>
#include <vector>
#include <sstream>
#include <algorithm>

CScopedLogger* CStationMgr::ms_pLogger = CScopedLogger::create("StationManager", LOG_LEVEL_DEBUG);
bool CStationMgr::m_bShowAllBlips = false; 

CStationMgr::CStationMgr() {}

bool compareDistance(std::pair<CStation*, float> a, std::pair<CStation*, float> b)
{
    return a.second < b.second;
}

void CStationMgr::onTick() {
    m_nFrames++;

    if(m_nFrames % NUM_FRAMES_FOR_MAP_RECALC == 0) {
        drawMapBlips();
    }

    for (CStation* station : g_stations) {
        station->render();

        if (station->m_bHasCheckpoint && station->inCheckpointBounds()) {
            ms_pLogger->debug("in checkpoint bounds!");
        }
    }
}

void CStationMgr::drawMapBlips() {
    // we assume that if we want to show all blips,
    // then there is some call doing this work for us...
    if (m_bShowAllBlips) return;



    ms_pLogger->trace("rendering station icons");
    CPed* ped = CPlayerInfo::GetPlayerInfo(CWorld::PlayerInFocus)->m_pPlayerPed;

    if(ped == nil) {
        ms_pLogger->trace("ped is nil - cannot render icons...");
    };

    // first, work out distances to all police stations
    CMatrix* location = ped->m_pMatrix;
    std::vector<std::pair<CStation*, float>> distances;

    for(CStation* station : g_stations) {
        CVector* blipVector = station->m_pBlipVector;   
        station->hide();

        float distance = sqrt(
            pow((location->pos.x - blipVector->x),2) +
            pow((location->pos.y - blipVector->y),2)
        );

        if (ms_pLogger->isEnabled(LOG_LEVEL_TRACE)) {
            std::ostringstream stream;
            stream << "distance calculated: ";
            stream << distance;

            ms_pLogger->trace(stream.str());
        }        

        distances.push_back(std::make_pair(station, distance));
    }

    // sort based on the distance to the station from smallest -> largest
    std::sort(
        distances.begin(),
        distances.end(),
        compareDistance
    );

    // select the closest 3 stations
    std::vector<std::pair<CStation*, float>> closest(distances.begin(), distances.begin() + MAX_NUM_BLIPS);

    for (auto elem : closest) {
        if (ms_pLogger->isEnabled(LOG_LEVEL_TRACE)) {
            std::ostringstream stream;
            stream << "closest: (x = " << elem.first->m_pBlipVector->x << ", y = " << elem.first->m_pBlipVector->y << ", z = " << elem.first->m_pBlipVector->z << ")";
            ms_pLogger->trace(stream.str());
        }

        elem.first->show();
        elem.first->m_bHasCheckpoint = true;
    }

    ms_pLogger->trace("rendered station icons");
};

void CStationMgr::showAllBlips() {
    for(CStation* station : g_stations) {
        station->_placeBlip();
    }

    m_bShowAllBlips = true;
}

void CStationMgr::drawCheckpoints() {
    for (CStation* station : g_stations) {
        station->_drawCheckpoint();
    }
}

void CStationMgr::showNearbyBlips() {
    for(CStation* station : g_stations) {
        station->_removeBlip();
    }

    drawMapBlips();
}