#include "skybox.hpp"

#include <rendering/mesh_consts.h>

#include <common/helpers.h>
#include <common/glutils.h>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


Skybox::Skybox(const Scene* parent)
    : Renderable(parent) {
}

void Skybox::render() const {
    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);
    Renderable::render();
}

glm::mat4x4 Skybox::getTransform() const {
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, -0.5f, -0.5f));
    return model;
}

std::vector<glm::vec3> Skybox::getVertices() const {
    std::vector<glm::vec3> vertices;
    for (const auto &cube_side : MeshConsts::cubeVerts) {
        for (const auto &vertex : cube_side) {
            vertices.push_back(vertex);
        }
    }
    return vertices;
}

std::vector<u32> Skybox::getIndices() const {
    std::vector<u32> indices;
    for (int i = 0; i < 6; ++i) {
        for (auto vertex : MeshConsts::faceIndicesInv) {
            indices.push_back(vertex + 4 * i);
        }
    }
    return indices;
}

GLuint Skybox::getShader() const {
	GLuint shader = 0;
    if (shaderLoadVF(&shader, SHADER_PATH "skybox.vert", SHADER_PATH "skybox.frag")) throw;
    return shader;
}
