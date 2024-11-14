#pragma once

#define walk_speed 0.1f
#define look_speed 0.01f
#include <iostream>

class Player {
public:
	Player() = default;

	Player(const Player &source) {
		memcpy(&this->position, &source.position, sizeof(glm::vec3));
		memcpy(&this->rotation, &source.rotation, sizeof(glm::vec3));
	}

	void update(const Input *input) {
		glm::vec2 delta = { input->get_cursor_delta().x, input->get_cursor_delta().y };
		
		rotation.x = glm::clamp(rotation.x - delta.y * look_speed, -glm::half_pi<f32>(), glm::half_pi<f32>());
		rotation.y = nixemath::wrap(rotation.y - delta.x * look_speed, 0, glm::two_pi<f32>());

		glm::vec3 dir = { 0, 0, 0};
		if (input->is_key_down(GLFW_KEY_W)) {
			dir.z -= 1;
		}

		if (input->is_key_down(GLFW_KEY_A)) {
			dir.x -= 1;
		}
	
		if (input->is_key_down(GLFW_KEY_S)) {
			dir.z += 1;
		}

		if (input->is_key_down(GLFW_KEY_D)) {
			dir.x += 1;
		}

		if (input->is_key_down(GLFW_KEY_SPACE)) {
			dir.y += 1;
		}

		if (input->is_key_down(GLFW_KEY_LEFT_CONTROL) || input->is_key_down(GLFW_KEY_LEFT_SHIFT)) {
			dir.y -= 1;
		}

		if (glm::length(dir) > 0) {
			dir = normalize(dir);
			float sin = glm::sin(rotation.y);
			float cos = glm::cos(rotation.y);
			glm::vec3 rotated_dir = {
				dir.x * cos + dir.z * sin,
				dir.y,
				dir.z * cos - dir.x * sin
			};
        
			position += rotated_dir * walk_speed;
		}
	}

	glm::vec3 position = { 0, 0, 0 };
	glm::vec3 rotation = { 0, 0, 0 };
};

#undef walk_speed
#undef look_speed
