#include "block_select.hpp"

#include <common/helpers.h>
#include <common/glutils.h>

#include <engine/scene.hpp>
#include <rendering/mesh_consts.hpp>

BlockSelect::BlockSelect(const Scene *parent) 
    : Renderable(parent, (u32)RenderConfig::Lines | (u32)RenderConfig::Indexed) {
    Renderable::init();
}

void BlockSelect::setTransform(glm::mat4 transform) {
	m_transform = transform;
}

void BlockSelect::setVisible(bool visible) {
    m_visible = visible;
}

void BlockSelect::render() const {
    if (!m_visible) return;
    Renderable::render();
}

glm::mat4 BlockSelect::getTransform() const {
    return m_transform;
}

void BlockSelect::setGLState() const {
	Renderable::setGLState();
    glDisable(GL_DEPTH_TEST);
    glLineWidth(4.0f);
}

std::vector<glm::vec3> BlockSelect::getVertices() const {
    return {
	    { 0, 0, 0 }, { 0, 0, 1 }, { 0, 1, 0 }, { 0, 1, 1 },
	    { 1, 0, 0 }, { 1, 0, 1 }, { 1, 1, 0 }, { 1, 1, 1 }
    };
}

std::vector<u32> BlockSelect::getIndices() const {
	return {
        0, 1,
        0, 2,
        1, 3,
        2, 3,
        4, 5,
        4, 6,
        5, 7,
        6, 7,
        0, 4,
        1, 5,
        2, 6,
        3, 7
    };
}

GLuint BlockSelect::getShader() const {
    GLuint shader = 0;
    if (shaderLoadVF(&shader, SHADER_PATH "black.vert", SHADER_PATH "black.frag")) throw;
    return shader;
}
