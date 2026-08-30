#pragma once

#include <common/types.h>

class StateProvider {
public:
    f32 getSpeed();

private:
    friend class Engine;

    f32 speed{};
};
