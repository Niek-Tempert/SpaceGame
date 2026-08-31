#include "line_renderable.h"

#include <glad/glad.h>

void MLineRenderable::_render() const {
	if (m_render_object->index_count > 0) {
		glDrawElements(GL_LINES, m_render_object->index_count, GL_UNSIGNED_INT, (void *)0);
		return;
	}

	glDrawArrays(GL_LINES, 0, m_render_object->vertex_count);
}
