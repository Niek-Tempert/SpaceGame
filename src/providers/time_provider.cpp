#include "time_provider.hpp"

TimeProvider::TimeProvider(f32 *time, f32 *deltaTime) {
	m_time = time;
	m_deltaTime = deltaTime;
}

TimeProvider::TimeProvider(const TimeProvider &provider) {
	m_time = provider.m_time;
	m_deltaTime = provider.m_deltaTime;
}

f32 TimeProvider::getTime() {
	return *m_time;
}

f32 TimeProvider::getDeltaTime() {
	return *m_deltaTime;
}
