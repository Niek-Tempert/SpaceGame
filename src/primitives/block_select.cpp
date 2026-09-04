#include "block_select.hpp"

#include <common/helpers.h>
#include <common/glutils.h>

BlockSelect::BlockSelect(const Scene *parent) 
    : Renderable(parent) {
    setRenderType(GL_LINES);
}

void BlockSelect::setTransform(glm::mat4 transform) {
	m_transform = transform;
}

void BlockSelect::setVisible(bool visible) {
    m_visible = visible;
}

void BlockSelect::render() {
    if (!m_visible) {
        return;
    }

    glDisable(GL_DEPTH_TEST);
    glLineWidth(4.0f);
    Renderable::render();
}

glm::mat4x4 BlockSelect::getTransform() const {
    return m_transform;
}

std::vector<glm::vec3> BlockSelect::getVertices() const {
    return {
        { 1, 0, 1 }, { 1, 1, 1 }, { 1, 1, 0 }, { 1, 0, 0 },
        { 0, 0, 0 }, { 0, 1, 0 }, { 0, 1, 1 }, { 0, 0, 1 },
        { 0, 1, 1 }, { 0, 1, 0 }, { 1, 1, 0 }, { 1, 1, 1 },
        { 0, 0, 0 }, { 0, 0, 1 }, { 1, 0, 1 }, { 1, 0, 0 },
        { 0, 0, 1 }, { 0, 1, 1 }, { 1, 1, 1 }, { 1, 0, 1 },
        { 1, 0, 0 }, { 1, 1, 0 }, { 0, 1, 0 }, { 0, 0, 0 },
        { 0, 0, 0 }, { 1, 0, 0 }, { 0, 0, 1 }, { 1, 0, 1 },
        { 0, 1, 0 }, { 1, 1, 0 }, { 0, 1, 1 }, { 1, 1, 1 }
    };
}

GLuint BlockSelect::getShader() const {
    GLuint shader = 0;
    if (shaderLoadVF(&shader, SHADER_PATH "black.vert", SHADER_PATH "black.frag")) throw;
    return shader;
}
