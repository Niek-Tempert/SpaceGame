#include "cube.hpp"

#include <rendering/mesh_consts.h>
#include <common/helpers.h>
#include <common/glutils.h>
#include <glad/glad.h>

Cube::Cube(const Scene* scene) 
    : Renderable(scene){
}

std::vector<glm::vec3> Cube::getVertices() const {
	std::vector<glm::vec3> vertices;
    for (const auto &cube_side : MeshConsts::cubeVerts) {
        for (const auto &vertex : cube_side) {
            vertices.push_back(vertex);
        }
    }
    return vertices;
}

std::vector<glm::vec3> Cube::getColors() const {
    std::vector<glm::vec3> colors;
    for (const auto &cube_side : MeshConsts::cubeVerts) {
        for (const auto &vertex : cube_side) {
            colors.push_back(vertex);
        }
    }
    return colors;
}

std::vector<u32> Cube::getIndices() const {
    std::vector<u32> indices;
    for (int i = 0; i < 6; ++i) {
        for (auto vertex : MeshConsts::faceIndices) {
            indices.push_back(vertex + 4 * i);
        }
    }
    return indices;
}

GLuint Cube::getShader() const {
    GLuint shader = 0;
    if (shaderLoadVF(&shader, SHADER_PATH "unlit.vert", SHADER_PATH "unlit.frag")) throw;
    return shader;
}
