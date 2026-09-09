#include "time_provider.hpp"

TimeProvider::TimeProvider(const f32* time, const f32* deltaTime) {
	m_time = time;
	m_deltaTime = deltaTime;
}

TimeProvider::TimeProvider(const TimeProvider* provider) {
	m_time = provider->m_time;
	m_deltaTime = provider->m_deltaTime;
}

f32 TimeProvider::getTime() const {
	return *m_time;
}

f32 TimeProvider::getDeltaTime() const {
	return *m_deltaTime;
}
