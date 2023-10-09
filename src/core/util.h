#ifndef _UTIL_H
#define _UTIL_H

#include "core/ivsdk.h"

namespace Utils 
{
    CVector* vectorAt(float x, float y, float z) {
        CVector* vec = new CVector();
        
        vec->x = x;
        vec->y = y;
        vec->z = z;

        return vec;
    }

    bool inRadius(CVector* pos, float radius) {
        auto loc = FindPlayerPed()->m_pMatrix;

        return sqrt(
            pow((loc->pos.x - pos->x),2) +
            pow((loc->pos.y - pos->y),2)
        ) < radius;
    }
}

#endif