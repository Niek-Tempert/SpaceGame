#pragma once

#include "../third_party/linmath.h"

class Player {
public:
	Player() = default;

	Player(const Player &source) {
		memcpy(&this->position, &source.position, sizeof(vec3));
		memcpy(&this->rotation, &source.rotation, sizeof(vec3));
	}

	vec3 position = { 0, 0, 0 };
	vec3 rotation = { 0, 0, 0 };
};
