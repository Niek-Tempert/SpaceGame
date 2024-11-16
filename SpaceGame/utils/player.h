#pragma once

#define walk_speed 4.0f
#define run_speed 8.0f
#define look_speed 0.01f

#include "program.h"

#include <iostream>

class Player {
public:
	Player() = default;

	Player(const Player &source) {
		memcpy(&this->position, &source.position, sizeof(glm::vec3));
		memcpy(&this->rotation, &source.rotation, sizeof(glm::vec3));
	}

	void update(const Program *program) {
		if (program->focussed) {
			glm::vec2 delta = { program->input->get_cursor_delta().x, program->input->get_cursor_delta().y };
			
			rotation.x = glm::clamp(rotation.x - delta.y * look_speed, -glm::half_pi<f32>(), glm::half_pi<f32>());
			rotation.y = nixemath::wrap(rotation.y - delta.x * look_speed, 0, glm::two_pi<f32>());
		}

		glm::vec3 dir = { 0, 0, 0};
		if (program->input->is_key_down(GLFW_KEY_W)) {
			dir.z -= 1;
		}

		if (program->input->is_key_down(GLFW_KEY_A)) {
			dir.x -= 1;
		}
	
		if (program->input->is_key_down(GLFW_KEY_S)) {
			dir.z += 1;
		}

		if (program->input->is_key_down(GLFW_KEY_D)) {
			dir.x += 1;
		}

		if (program->input->is_key_down(GLFW_KEY_SPACE)) {
			dir.y += 1;
		}

		if (program->input->is_key_down(GLFW_KEY_LEFT_CONTROL)) {
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

			f32 speed;
			if (program->input->is_key_down(GLFW_KEY_LEFT_SHIFT)) {
				speed = run_speed;
			} else {
				speed = walk_speed;
			}
				
			position += rotated_dir * (f32)program->delta_time * speed;
		}
	}

	glm::vec3 position = { 0, 0, 0 };
	glm::vec3 rotation = { 0, 0, 0 };
};

#undef walk_speed
#undef look_speed
