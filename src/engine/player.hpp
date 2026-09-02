#pragma once

#include <glm/vec3.hpp>

#include <common/types.h>
#include <providers/input_provider.hpp>

class Input;

class Player
	: InputProvider {
public:
	Player(const InputProvider& provider);
	void update(f32 deltaTime);
	glm::vec3 getPos() const;
	glm::vec3 getRot() const;

private:
	glm::vec3 m_pos;
	glm::vec3 m_rot;
};
