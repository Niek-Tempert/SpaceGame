#include "player.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "input.hpp"
#include <common/math.h>

#define WALK_SPEED 4.0f
#define RUN_SPEED 8.0f
#define LOOK_SPEED 0.01f

Player::Player(const InputProvider& input, const TimeProvider& time) 
    : InputProvider(input)
    , TimeProvider(time)
    , m_pos()
    , m_rot() {
}

void Player::update() {
	glm::vec2 delta = {
        getCursorDelta().x,
        getCursorDelta().y 
    };
	
	m_rot.x = glm::clamp(m_rot.x - delta.y * LOOK_SPEED, -glm::half_pi<f32>(), glm::half_pi<f32>());
	m_rot.y = wrap(m_rot.y - delta.x * LOOK_SPEED, 0, glm::two_pi<f32>());

	glm::vec3 dir{};
	if (getKeyDown(GLFW_KEY_W)) dir.z -= 1;
	if (getKeyDown(GLFW_KEY_A)) dir.x -= 1;
	if (getKeyDown(GLFW_KEY_S)) dir.z += 1;
	if (getKeyDown(GLFW_KEY_D)) dir.x += 1;
	if (getKeyDown(GLFW_KEY_SPACE)) dir.y += 1;
	if (getKeyDown(GLFW_KEY_LEFT_CONTROL)) dir.y -= 1;
	if (glm::length(dir) <= 0) return;

    dir = normalize(dir);
    f32 sin = glm::sin(m_rot.y);
    f32 cos = glm::cos(m_rot.y);
    glm::vec3 rotated_dir = {
        dir.x * cos + dir.z * sin,
        dir.y,
        dir.z * cos - dir.x * sin
    };

    f32 speed = getKeyDown(GLFW_KEY_LEFT_SHIFT) 
        ? RUN_SPEED 
        : WALK_SPEED;

    m_pos += rotated_dir * getDeltaTime() * speed;
}

glm::vec3 Player::getPos() const {
	return m_pos;
}

glm::vec3 Player::getRot() const {
	return m_rot;
}
