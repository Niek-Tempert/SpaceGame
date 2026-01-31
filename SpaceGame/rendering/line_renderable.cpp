#include "line_renderable.h"

#include <glad/glad.h>

void MLineRenderable::_render() const {
	if (_render_object->index_count > 0) {
		glDrawElements(GL_LINES, _render_object->index_count, GL_UNSIGNED_INT, (void *)0);
	} else {
		glDrawArrays(GL_LINES, 0, _render_object->vertex_count);
	}
}
