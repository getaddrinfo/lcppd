#include "vehicle.h"

CScopedLogger* CDutyVehicle::ms_pLogger = CScopedLogger::create("Vehicle");

CDutyVehicle::CDutyVehicle(Scripting::Vehicle handle) {
    std::ostringstream stream;

    uint32_t pModelId;
    Scripting::GET_CAR_MODEL(handle, &pModelId);

    m_sModelName = Scripting::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(pModelId);
    m_vehicleHandle = handle;
    
    markUnreapable();
    addBlip();

    stream << "registered duty vehicle: " << m_sModelName;
    ms_pLogger->info(stream.str());
}  

// This constructor is useful for debugging...
CDutyVehicle::CDutyVehicle(std::string model) {
    auto hash = rage::atStringHash(model.c_str());

    int idx;
    auto mdl = CModelInfo::GetModelInfo(hash, &idx);
    
    Scripting::Vehicle handle;

    CStreaming::ScriptRequestModel(hash);
    CStreaming::LoadAllRequestedModels(0);
    CMatrix mat = *FindPlayerPed()->m_pMatrix;
    mat.pos.x += 2;

    Scripting::CREATE_CAR(
        hash,
        mat.pos.x,
        mat.pos.y,
        mat.pos.z,
        &handle,
        true
    );

    m_vehicleHandle = handle;
    m_sModelName = model;

    markUnreapable();
    addBlip();

    std::ostringstream stream;
    stream << "registered duty vehicle: " << m_sModelName;
    ms_pLogger->info(stream.str());
}

CDutyVehicle::~CDutyVehicle() {
    markReapable();
    removeBlip();
}

void CDutyVehicle::markUnreapable() {
    Scripting::SET_CAR_AS_MISSION_CAR(m_vehicleHandle);
    m_bIsUnreapable = true;
}

void CDutyVehicle::markReapable() {
    Scripting::MARK_CAR_AS_NO_LONGER_NEEDED(&m_vehicleHandle);
    m_bIsUnreapable = false;
}

void CDutyVehicle::addBlip() {
    Scripting::Blip blipHandle;

    Scripting::ADD_BLIP_FOR_CAR(m_vehicleHandle, &blipHandle);
    Scripting::CHANGE_BLIP_SPRITE(blipHandle, SPRITE_CAR);
    Scripting::CHANGE_BLIP_DISPLAY(blipHandle, BLIP_DISPLAY_MAP_ONLY);
    Scripting::CHANGE_BLIP_SCALE(blipHandle, 0.5);

    m_blipHandle = blipHandle;
    m_bHasBlip = true;
};

void CDutyVehicle::removeBlip() {
    Scripting::REMOVE_BLIP(m_blipHandle);
    m_bHasBlip = false;
}