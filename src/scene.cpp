#include "scene.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "utils/input.hpp"

static void buildVoxel(Voxel *voxel, int length, glm::vec3 position) {
	for (int x = -length; x < length; ++x) {
		for (int y = -length; y < length; ++y) {
			for (int z = -length; z < length; ++z) {
				glm::vec3 vec = { (float)x, (float)y, (float)z };
				if (glm::length(vec) > (float)length) {
					continue;
				}

				voxel->set({ x, y, z }, { (ICell *)1, NULL });
			}
		}
	}

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	voxel->transform = model;
}

void Scene::init() {
	buildVoxel(&m_planet, 16, { 0, -17, 0 });
	buildVoxel(&m_moon, 8, { 0, 0, 32 });

    m_skybox.init();
    m_block_cursor.init();
    m_cursor.init();
    m_planet.init();
    m_moon.init();

    m_voxels.push_back(&m_planet);
    m_voxels.push_back(&m_moon);
    
    m_renderables.push_back(&m_skybox);
	m_renderables.push_back(&m_planet);
	m_renderables.push_back(&m_moon);
	m_renderables.push_back(&m_block_cursor);
	m_renderables.push_back(&m_cursor);
}

void Scene::update(const Input* input) {
    updatePlayer(input);
    updateMoon();

    glm::mat4 rot = glm::mat4(1.0f);
	rot = glm::rotate(rot, player.getRot().z, glm::vec3(0, 0, 1));
	rot = glm::rotate(rot, player.getRot().y, glm::vec3(0, 1, 0));
	rot = glm::rotate(rot, player.getRot().x, glm::vec3(1, 0, 0));
	glm::vec3 direction = rot * glm::vec4(0, 0, -1, 1);

	f32 dist = 4.0f;
	RaycastResult result;
	Voxel *hit_voxel = nullptr;
	for (Voxel* voxel : m_voxels) {
		RaycastResult voxel_result = voxel->raycast(
            { 
                player.getPos().x, 
                player.getPos().y, 
                player.getPos().z 
            },
            {
                direction.x,
                direction.y,
                direction.z
            },
            dist
        );

		if (voxel_result.hit) {
			hit_voxel = voxel;
			dist = result.distance;
			result = voxel_result;
		}
	}

	m_block_cursor.visible = result.hit;
	if (!result.hit) return;

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(result.id.x, result.id.y, result.id.z));
    model = hit_voxel->transform * model;
    m_block_cursor.transform = model;

    if (input->is_mouse_press(GLFW_MOUSE_BUTTON_1) && result.hit) {
        hit_voxel->set(result.id, { NULL, NULL });
        hit_voxel->update(result.id);
    }

    if (input->is_mouse_press(GLFW_MOUSE_BUTTON_2) && result.hit) {
        hit_voxel->set(result.id + result.normal, { (ICell *)1, NULL });
        hit_voxel->update(result.id + result.normal);
    }
}

glm::mat4 Scene::getView() {
	return m_view;
}

std::vector<IRenderable*> Scene::getRenderables() {
	return m_renderables;
}

void Scene::updatePlayer(const Input *input) {
    player.update(getDeltaTime(), input);

    glm::mat4 rot = glm::mat4(1.0f);
	rot = glm::rotate(rot, -player.getRot().x, glm::vec3(1, 0, 0));
	rot = glm::rotate(rot, -player.getRot().y, glm::vec3(0, 1, 0));
	rot = glm::rotate(rot, -player.getRot().z, glm::vec3(0, 0, 1));
    m_view = rot * glm::translate(glm::mat4(1.0f), -player.getPos());
}

void Scene::updateMoon() {
    glm::vec3 position = glm::vec3(m_moon.transform[3]);
	f64 t = getDeltaTime() * 0.05 * getSpeed();
	f64 sin = glm::sin(t);
	f64 cos = glm::cos(t);
	glm::vec3 rotated_pos = {
		position.x * cos + position.z * sin,
		position.y,
		position.z * cos - position.x * sin
	};

	m_moon.transform = glm::translate(glm::mat4(1.0f), rotated_pos);
}
