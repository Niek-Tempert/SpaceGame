#pragma once

class Player {
public:
	Player() = default;

	Player(const Player &source) {
		memcpy(&this->position, &source.position, sizeof(glm::vec3));
		memcpy(&this->rotation, &source.rotation, sizeof(glm::vec3));
	}

	glm::vec3 position = { 0, 0, 0 };
	glm::vec3 rotation = { 0, 0, 0 };
};
