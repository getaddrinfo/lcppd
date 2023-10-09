#include "interiormgr.h"
#include "vehicle/vehiclemgr.h"
#include "core/util.h"

#include <sstream>

// trace while working on it
CScopedLogger* CInteriorMgr::ms_pLogger = CScopedLogger::create("Interior", LOG_LEVEL_TRACE);
CVector* CInteriorMgr::ms_pSpawnPosition = Utils::vectorAt(98.44, -683.27, 14.77);
CVector* CInteriorMgr::ms_pLeavePosition = Utils::vectorAt(96.25, -683.35, 13.47);


CInteriorMgr::CInteriorMgr(CStation* source) {
    m_pSourceStation = source;
    m_bIsActive = false;
    m_bIsInStation = false;
    m_bIsFinished = false;
}

CInteriorMgr::~CInteriorMgr() {}

// streams in all the models...
void CInteriorMgr::_stream() {
    // TODO: can we do this to improve performance?
}

void CInteriorMgr::_exit() {
    CPed* player = FindPlayerPed();

    if (player == nil) {
        ms_pLogger->error("player is nil - cannot warp");
        return;
    }

    // set after the nil check so that it can be retried
    m_bIsInStation = false;

    Scripting::Ped playerHandle = CPools::ms_pPedPool->GetIndex(player);

    player->Teleport(
        m_pSourceStation->m_pCarChooseVector,
        false,
        true
    );

    Scripting::SET_CHAR_HEADING(
        playerHandle,
        m_pSourceStation->m_fCarChooseHeading
    );

    // we are no longer in the station, so stop running
    // station tasks
    m_bIsActive = false;
    m_bIsFinished = true;

    // let the vehicle manager take over
    // CVehicleMgr::ms_bIsPickingVehicle = true;
}

void CInteriorMgr::_disarm() {
    // get the handle for the current player
    CPed* player = FindPlayerPed();
    uint32_t handle = CPools::ms_pPedPool->GetIndex(player);

    // unarm them and disallow changing weapons
    ms_pLogger->trace("blocking weapon switching");
    Scripting::BLOCK_PED_WEAPON_SWITCHING(handle, false);
    Scripting::TASK_SWAP_WEAPON(handle, WEAPON_UNARMED);
    Scripting::BLOCK_PED_WEAPON_SWITCHING(handle, true);
    ms_pLogger->trace("blocked weapon switching");
}

void CInteriorMgr::_warp() {
    ms_pLogger->trace("warping player");

    CPed* player = FindPlayerPed();

    if (player == nil) {
        ms_pLogger->warn("player is nil, cannot teleport");
        return;
    }

    player->Teleport(
        ms_pSpawnPosition,
        false,
        true
    );

    ms_pLogger->trace("warped player");
}

void CInteriorMgr::teleport() {
    m_bIsActive = true;
    ms_pLogger->trace("fading out screen");

    Scripting::FORCE_LOADING_SCREEN(true);

    // _stream(); // does nothing atm...
    _disarm();
    _warp();

    m_bIsInStation = true;

    // TODO: teleport into the building
    // TODO: register all the checkpoints
    // TODO: clothes selection

    
    ms_pLogger->trace("fading in screen");
    Scripting::FORCE_LOADING_SCREEN(false);
}

void CInteriorMgr::onTick() {
    // if we aren't currently in the station, don't do anything
    if (!m_bIsActive) return;
    
    // if we are in the station, and we are in the leave checkpoint, warp us to choosing a car
    if (m_bIsInStation && Utils::inRadius(ms_pLeavePosition, LEAVE_CHECKPOINT_RADIUS)) {
        _exit();
        return;
    }
}

void CInteriorMgr::_render() {
    // draw a yellow checkpoint
    Scripting::DRAW_CHECKPOINT(
        CInteriorMgr::ms_pLeavePosition->x,
        CInteriorMgr::ms_pLeavePosition->y,
        CInteriorMgr::ms_pLeavePosition->z,
        LEAVE_CHECKPOINT_RADIUS,
        255, // r
        255, // g
        0 // b
    );
}