#pragma once

#include <common/types.h>

class TimeProvider {
public:
    TimeProvider(f32* time, f32* deltaTime);
    TimeProvider(const TimeProvider& provider);

protected:
    f32 getTime();
    f32 getDeltaTime();

private:
    f32* m_time;
    f32* m_deltaTime;
};
