#include "crossair.hpp"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>
#include <common/glutils.h>
#include <engine/scene.hpp>

Crossair::Crossair(const Scene* parent) 
    : Renderable(parent)
    , CanvasProvider(parent) {
    setRenderType(GL_LINES);
}

void Crossair::setGLState() const {
    Renderable::setGLState();
    glLineWidth(4.0f);
}

glm::mat4 Crossair::getView() const {
    glm::ivec2 size = getSize();
    glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3((f32)size.x / 2.0f, (f32)size.y / 2.0f, 0.0f));
    glm::mat4 ortho = glm::ortho(0.0f, (f32)size.x, 0.0f, (f32)size.y, 1.0f, -1.0f);
    glm::mat4 view = ortho * trans;
    return view;
}

std::vector<glm::vec3> Crossair::getVertices() const {
    return {
        { -16.0f, 0.0f, 0.0f },
        { 16.0f, 0.0f, 0.0f },
        { 0.0f, -16.0f, 0.0f },
        { 0.0f, 16.0f, 0.0f }
    };
}

GLuint Crossair::getShader() const {
    GLuint shader = 0;
    if (shaderLoadVF(&shader, SHADER_PATH "cursor.vert", SHADER_PATH "cursor.frag")) throw;
    return shader;
}
