#pragma once

#include <glm/vec3.hpp>

#include <common/types.h>

class Input;

class Player {
public:
	void update(f32 deltaTime, const Input* input);
	glm::vec3 getPos() const;
	glm::vec3 getRot() const;

private:
	glm::vec3 m_pos{};
	glm::vec3 m_rot{};
};
