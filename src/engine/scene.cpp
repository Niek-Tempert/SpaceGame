#include "scene.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "input.hpp"
#include "engine.hpp"
#include <imgui.h>

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
	voxel->m_transform = model;
	voxel->rebuildMesh();
}

Scene::Scene(const InputProvider& input, const TimeProvider& time)
	: InputProvider(input)
	, TimeProvider(time)
	, m_skybox()
	, m_moon()
	, m_planet()
	, m_blockSelect()
	, m_crossair()
	, m_voxels()
	, m_player(this)
	, m_view(glm::mat4(1.0f))
	, m_moonSpeed(1.f) {
	buildVoxel(&m_planet, 16, { 0, -17, 0 });
	buildVoxel(&m_moon, 8, { 0, 0, 32 });

	m_skybox.rebuildMesh();
	m_blockSelect.rebuildMesh();
	m_crossair.rebuildMesh();

    m_voxels.push_back(&m_planet);
    m_voxels.push_back(&m_moon);
    
    m_renderables.push_back(&m_skybox);
	m_renderables.push_back(&m_planet);
	m_renderables.push_back(&m_moon);
	m_renderables.push_back(&m_blockSelect);
	m_renderables.push_back(&m_crossair);
}

void Scene::update() {
    updatePlayer();
    updateMoon();
	makeUI();

    glm::mat4 rot = glm::mat4(1.0f);
	rot = glm::rotate(rot, m_player.getRot().z, glm::vec3(0, 0, 1));
	rot = glm::rotate(rot, m_player.getRot().y, glm::vec3(0, 1, 0));
	rot = glm::rotate(rot, m_player.getRot().x, glm::vec3(1, 0, 0));
	glm::vec3 direction = rot * glm::vec4(0, 0, -1, 1);

	f32 dist = 4.0f;
	RaycastResult result;
	Voxel *hit_voxel = nullptr;
	for (Voxel* voxel : m_voxels) {
		RaycastResult voxel_result = voxel->raycast(
            { 
                m_player.getPos().x, 
                m_player.getPos().y, 
                m_player.getPos().z 
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

	m_blockSelect.setVisible(result.hit);
	if (!result.hit) return;

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(result.id.x, result.id.y, result.id.z));
    model = hit_voxel->m_transform * model;
    m_blockSelect.setTransform(model);

    if (getMouse(GLFW_MOUSE_BUTTON_1) && result.hit) {
        hit_voxel->set(result.id, { NULL, NULL });
        hit_voxel->update(result.id);
    }

    if (getMouse(GLFW_MOUSE_BUTTON_2) && result.hit) {
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

void Scene::updatePlayer() {
    m_player.update();

    glm::mat4 rot = glm::mat4(1.0f);
	rot = glm::rotate(rot, -m_player.getRot().x, glm::vec3(1, 0, 0));
	rot = glm::rotate(rot, -m_player.getRot().y, glm::vec3(0, 1, 0));
	rot = glm::rotate(rot, -m_player.getRot().z, glm::vec3(0, 0, 1));
    m_view = rot * glm::translate(glm::mat4(1.0f), -m_player.getPos());
}

void Scene::updateMoon() {
    glm::vec3 position = glm::vec3(m_moon.m_transform[3]);
	f64 t = getDeltaTime() * 0.05 * m_moonSpeed;
	f64 sin = glm::sin(t);
	f64 cos = glm::cos(t);
	glm::vec3 rotated_pos = {
		position.x * cos + position.z * sin,
		position.y,
		position.z * cos - position.x * sin
	};

	m_moon.m_transform = glm::translate(glm::mat4(1.0f), rotated_pos);
}

void Scene::makeUI() {
	ImGui::Begin("Settings");
	ImGui::DragFloat("Moon speed", &m_moonSpeed, 0.01f);
	ImGui::End();
}
