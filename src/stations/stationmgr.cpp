#include "stationmgr.h"

#include <cmath>
#include <vector>
#include <sstream>
#include <algorithm>

CScopedLogger* CStationMgr::ms_pLogger = CScopedLogger::create("StationManager", LOG_LEVEL_DEBUG);
bool CStationMgr::m_bShowAllBlips = false; 

CStationMgr::CStationMgr() {
    m_pInterior = nil;
}

bool compareDistance(std::pair<CStation*, float> a, std::pair<CStation*, float> b)
{
    return a.second < b.second;
}

void CStationMgr::onTick() {
    m_nFrames++;

    if(m_nFrames % NUM_FRAMES_FOR_MAP_RECALC == 0) {
        drawMapBlips();
    }
    
    if (m_pInterior != nil) {
        // if it's finished, dealloc it
        if (m_pInterior->m_bIsFinished) {
            delete m_pInterior;
            m_pInterior = nil;
        } else {
            m_pInterior->onTick();
        }
    }

    for (CStation* station : g_stations) {
        station->render();

        // if the station has a checkpoint, and we have
        // no interior manager, and we are in the checkpoint,
        // teleport to the interior
        if (station->m_bHasCheckpoint && m_pInterior == nil && station->inCheckpointBounds()) {
            ms_pLogger->debug("in checkpoint bounds!");
            m_pInterior = new CInteriorMgr(station);
            m_pInterior->teleport();
        }
    }
}

void CStationMgr::drawMapBlips() {
    // if m_bShowAllBlips is true, drawing work is done elsewhere
    //
    // if m_pInterior->m_bIsActive then we don't want to show icons on the map
    // as we are actually in a police station
    if (m_bShowAllBlips || (m_pInterior != nil && m_pInterior->m_bIsActive)) return;

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