#include "stations.h"
#include <cmath>

#include <vector>
#include <sstream>
#include <algorithm>


#define MAX_NUM_BLIPS 3

CScopedLogger* CStationMgr::ms_pLogger = CScopedLogger::create("StationManager");
CStationMgr::CStationMgr() {}

bool compareDistance(std::pair<CStation*, float> a, std::pair<CStation*, float> b)
{
    return a.second < b.second;
}

void CStationMgr::render() {
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
        station->removeBlip();

        float distance = sqrt(
            pow((location->pos.x - blipVector->x),2) +
            pow((location->pos.y - blipVector->y),2)
        );

        if (CLogger::isEnabled(ELL_TRACE)) {
            std::ostringstream stream;
            stream << "distance calculated: ";
            stream << distance;

            ms_pLogger->trace(stream.str());
        }        

        distances.push_back(std::make_pair(station, distance));
    }

    std::sort(
        distances.begin(),
        distances.end(),
        compareDistance
    );

    std::vector<std::pair<CStation*, float>> closest(distances.begin(), distances.begin() + MAX_NUM_BLIPS);

    for (auto elem : closest) {
        if (CLogger::isEnabled(ELL_TRACE)) {
            std::ostringstream stream;
            stream << "closest: (x = " << elem.first->m_pBlipVector->x << ", y = " << elem.first->m_pBlipVector->y << ", z = " << elem.first->m_pBlipVector->z << ")";
            ms_pLogger->trace(stream.str());
        }

        elem.first->placeBlip();
    }

    ms_pLogger->trace("rendered station icons");
}