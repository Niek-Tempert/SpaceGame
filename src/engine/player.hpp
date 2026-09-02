#pragma once

#include <glm/vec3.hpp>

#include <common/types.h>
#include <providers/input_provider.hpp>
#include <providers/time_provider.hpp>

class Scene;

class Player
	: InputProvider
	, TimeProvider {
public:
	Player(const Scene* parent);
	void update();
	glm::vec3 getPos() const;
	glm::vec3 getRot() const;

private:
	glm::vec3 m_pos;
	glm::vec3 m_rot;
};
