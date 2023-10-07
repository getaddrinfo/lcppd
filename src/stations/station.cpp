#include "station.h"


CScopedLogger* CStation::g_log = CScopedLogger::create("Station");

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
    m_bHasPlacedBlip = false;
}

void CStation::placeBlip() {
    if (m_bHasPlacedBlip) return;

    Scripting::Blip onMapBlipHandle;
    Scripting::Blip onGroundBlipHandle;


    // Map blip
    Scripting::ADD_BLIP_FOR_COORD(
        m_pBlipVector->x,
        m_pBlipVector->y,
        m_pBlipVector->z,
        &onMapBlipHandle
    );

    Scripting::CHANGE_BLIP_SPRITE(
        onMapBlipHandle,
        Scripting::BLIP_POLICE_STATION
    );

    // Entry point (ground)
    Scripting::ADD_BLIP_FOR_COORD(
        m_pBlipVector->x,
        m_pBlipVector->y,
        m_pBlipVector->z,
        &onGroundBlipHandle
    );

    Scripting::CHANGE_BLIP_SPRITE(
        onGroundBlipHandle,
        Scripting::BLIP_OBJECTIVE
    );

    Scripting::CHANGE_BLIP_DISPLAY(
        onGroundBlipHandle,
        BLIP_DISPLAY_ARROW_ONLY
    );

    m_mapBlipHandle = onMapBlipHandle;
    m_groundBlipHandle = onGroundBlipHandle;

    m_bHasPlacedBlip = true;
}

void CStation::removeBlip() {
    if (!m_bHasPlacedBlip) return;

    Scripting::REMOVE_BLIP(m_mapBlipHandle);
    Scripting::REMOVE_BLIP(m_groundBlipHandle);

    m_bHasPlacedBlip = false;
}

CStation::~CStation() {
    delete m_pBlipVector;
    delete m_pCarChooseVector;

    removeBlip();
}