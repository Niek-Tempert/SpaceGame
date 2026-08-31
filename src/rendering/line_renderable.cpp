#include "line_renderable.h"

#include <glad/glad.h>

void MLineRenderable::draw() const {
	if (m_renderObject->idxCt > 0) {
		glDrawElements(GL_LINES, m_renderObject->idxCt, GL_UNSIGNED_INT, (void *)0);
		return;
	}

	glDrawArrays(GL_LINES, 0, m_renderObject->vertCt);
}
