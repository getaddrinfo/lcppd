#ifndef _INTERIOR_H
#define _INTERIOR_H

#include "core/common.h"
#include "core/scopedlogger.h"
#include "stations/station.h"

#include <vector>
#include <string>

class CInterior
{
public:
    static CScopedLogger* ms_pLogger;

    static CStation* ms_pSourceStation;
    static bool ms_bIsInStation;
    static std::vector<std::string> ms_vRoomStreamIds;


    // teleports to the interior from the given CStation*
    // source is used to define where to return to for picking a car.
    static void teleport(CStation* source);

    // streams in the necessary models
    static void _stream();

    // teleports to the choose car location
    static void _chooseCar();
};  

#endif _INTERIOR_H