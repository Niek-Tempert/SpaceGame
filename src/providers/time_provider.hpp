#pragma once

#include <common/types.h>

class TimeProvider {
public:
    TimeProvider(const f32* time, const f32* deltaTime);
    TimeProvider(const TimeProvider* provider);

protected:
    f32 getTime() const;
    f32 getDeltaTime() const;

private:
    const f32* m_time;
    const f32* m_deltaTime;
};
