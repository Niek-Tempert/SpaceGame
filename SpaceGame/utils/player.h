#pragma once

#define walk_speed 0.1f
#define look_speed 0.01f

class Player {
public:
	Player() = default;

	Player(const Player &source) {
		memcpy(&this->position, &source.position, sizeof(glm::vec3));
		memcpy(&this->rotation, &source.rotation, sizeof(glm::vec3));
	}

	void update(const Input *input) {
		glm::vec2 delta = { input->get_cursor_delta().x, input->get_cursor_delta().y };
	
		rotation.x = glm::clamp(rotation.x + delta.y * look_speed, -1.f, 1.f);
		rotation.y = nixemath::wrap(rotation.y + delta.x * look_speed, -glm::pi<f32>(), glm::pi<f32>());

		glm::vec3 dir = { 0, 0, 0};
		if (input->is_key_down(GLFW_KEY_W)) {
			dir += glm::vec3(glm::sin(rotation.y), 0, glm::cos(rotation.y));
		}

		if (input->is_key_down(GLFW_KEY_A)) {
			dir += glm::vec3(glm::cos(rotation.y), 0, -glm::sin(rotation.y));
		}
	
		if (input->is_key_down(GLFW_KEY_S)) {
			dir += glm::vec3(-glm::sin(rotation.y), 0, -glm::cos(rotation.y));
		}

		if (input->is_key_down(GLFW_KEY_D)) {
			dir += glm::vec3(-glm::cos(rotation.y), 0, glm::sin(rotation.y));
		}

		if (glm::length(dir) > 0) {
			position += glm::normalize(dir) * walk_speed;
		}
	}

	glm::vec3 position = { 0, 0, 0 };
	glm::vec2 rotation = { 0, 0 };
};

#undef walk_speed
#undef look_speed