#pragma once

#include <common/types.h>

class StateProvider {
protected:
    f32 getSpeed();

private:
    friend class Engine;

    f32 m_speed = 1;
};
