#ifndef _INTERIOR_MGR_H
#define _INTERIOR_MGR_H

#include "core/common.h"
#include "core/scopedlogger.h"
#include "stations/station.h"

#include <vector>
#include <string>

#define LEAVE_CHECKPOINT_RADIUS 1


class CInteriorMgr
{
public:
    static CScopedLogger* ms_pLogger;
    static CVector* ms_pSpawnPosition;
    static CVector* ms_pLeavePosition;

    CStation* m_pSourceStation;
    bool m_bIsInStation;
    bool m_bIsActive;
    bool m_bIsFinished;

    CInteriorMgr(CStation* source);
    ~CInteriorMgr();

    // teleports to the interior from the given CStation*
    // source is used to define where to return to for picking a car.
    void teleport();

    void onTick();
    void isInLeaveCheckpointBounds();

    // draws checkpoints
    void _render();

    // streams in the necessary models
    void _stream();

    // sets weapon to none and disallows changing
    void _disarm();

    // warps the user to the building interior
    void _warp();

    // teleports to the choose car location - called when
    // within the radius of checkpoint at ms_pLeavePosition
    void _exit();
};  

#endif _INTERIOR_MGR_H