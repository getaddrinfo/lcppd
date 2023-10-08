#include "station.h"
#include <cmath>

CScopedLogger* CStation::ms_pLogger = CScopedLogger::create("Station", LOG_LEVEL_DEBUG);

CStation::CStation(
    Vector blip,
    Vector choose,
    float chooseHeading
) {
    CVector* blipVec = new CVector();
    blipVec->x = blip.x;
    blipVec->y = blip.y;
    blipVec->z = blip.z;

    m_pBlipVector = blipVec;

    CVector* chooseVec = new CVector();
    chooseVec->x = choose.x;
    chooseVec->y = choose.y;
    chooseVec->z = choose.z;

    m_pCarChooseVector = chooseVec;
    m_fCarChooseHeading = chooseHeading;
    m_bHasBlip = false;
}


void CStation::show() {
    m_bHasCheckpoint = true;
    _placeBlip();
}

void CStation::hide() {
    m_bHasCheckpoint = false;
    _removeBlip();
}

void CStation::render() {
    _drawCheckpoint();
}

bool CStation::inCheckpointBounds() {
    auto loc = FindPlayerPed()->m_pMatrix;
    auto blipVector = m_pBlipVector;

    return sqrt(
        pow((loc->pos.x - blipVector->x),2) +
        pow((loc->pos.y - blipVector->y),2)
    ) <= ENTRANCE_RADIUS;
}

void CStation::_placeBlip() {
    if (m_bHasBlip) return;

    Scripting::Blip onMapBlipHandle;

    // Add blip
    Scripting::ADD_BLIP_FOR_COORD(
        m_pBlipVector->x,
        m_pBlipVector->y,
        m_pBlipVector->z,
        &onMapBlipHandle
    );

    // Make it a police station on the map
    Scripting::CHANGE_BLIP_SPRITE(
        onMapBlipHandle,
        Scripting::BLIP_POLICE_STATION
    );

    Scripting::CHANGE_BLIP_DISPLAY(
        onMapBlipHandle,
        BLIP_DISPLAY_MAP_ONLY
    );

    m_nBlipHandle = onMapBlipHandle;
    m_bHasBlip = true;
}

void CStation::_removeBlip() {
    if (!m_bHasBlip) return;

    ms_pLogger->trace("removing blip");
    Scripting::REMOVE_BLIP(m_nBlipHandle);
    ms_pLogger->trace("removed blip");

    m_bHasBlip = false;
}

void CStation::_placeEntrance() {
    if (m_bHasCheckpoint) return;

    int checkpointHandle = Scripting::CREATE_CHECKPOINT(
        1,
        m_pBlipVector->x,
        m_pBlipVector->y,
        m_pBlipVector->z,
        0,
        ENTRANCE_RADIUS // I think this is correct...
    );

    m_nCheckpointHandle = checkpointHandle;
    m_bHasCheckpoint = true;
}

void CStation::_removeEntrance() {
    if (!m_bHasCheckpoint) return;

    Scripting::DELETE_CHECKPOINT(m_nCheckpointHandle);
    m_bHasCheckpoint = false;
}

void CStation::_drawCheckpoint() {
    if (!m_bHasCheckpoint) return;

    Scripting::DRAW_CHECKPOINT(
        m_pBlipVector->x,
        m_pBlipVector->y,
        m_pBlipVector->z,
        ENTRANCE_RADIUS, 
        255, // r 
        0, // g
        0 // b
    );
}

CStation::~CStation() {
    delete m_pBlipVector;
    delete m_pCarChooseVector;

    _removeBlip();
    _removeEntrance();
    
}