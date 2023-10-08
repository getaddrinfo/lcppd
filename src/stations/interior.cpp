#include "interior.h"

// trace while I work on it
CScopedLogger* CInterior::ms_pLogger = CScopedLogger::create("Interior", LOG_LEVEL_TRACE);

std::vector<std::string> CInterior::ms_vRoomStreamIds = {
    "R_F6227E42_0000FA09",
    "R_8045126D_0000270A",
    "R_8F0EB000_0000F504",
    "R_B99E853B_00002A0D"
};

// streams in all the models...
void CInterior::_stream() {
    // TODO: complete streaming implementation 

    // for (auto modelName : ms_vRoomStreamIds) {
    //     Scripting::REQUEST_INTERIOR_MODELS(rage::atStringHash(modelName.c_str()), &modelName);
    // }
}

void CInterior::_chooseCar() {
    // TODO: vehicle selection
}

void CInterior::teleport(CStation* source) {
    ms_pSourceStation = source;

    _stream();

    // TODO: teleport into the building
    // TODO: register all the checkpoints
    // TODO: clothes selection

    ms_bIsInStation = true;
}