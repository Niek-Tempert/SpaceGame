#pragma once

#include <common/types.h>

class TimeProvider {
public:
    f32 getDeltaTime();
    f32 getTime();

private:
    friend class Engine;

    f32 m_deltaTime{};
    f32 m_time{};
};
