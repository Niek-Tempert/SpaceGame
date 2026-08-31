#include "time_provider.hpp"

f32 TimeProvider::getDeltaTime() {
	return m_deltaTime;
}

f32 TimeProvider::getTime() {
	return m_time;
}
