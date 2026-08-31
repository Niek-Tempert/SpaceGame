#include "chunk.h"

#include "chunk_mesher.h"
#include "cell/cell_user.h"

Chunk::Chunk(): m_mesher(new ChunkMesher()), m_cells(), m_count(0) {
}

void Chunk::set(const glm::uvec3 &id, const CellUser &cell) {
	if ((cell.type || cell.data)
		&& (!m_cells[id.x][id.y][id.z].type && !m_cells[id.x][id.y][id.z].data)) {
		m_count++;
	} else if ((!cell.type && !cell.data)
		&& (m_cells[id.x][id.y][id.z].type || m_cells[id.x][id.y][id.z].data)) {
		m_count--;
	}

	m_cells[id.x][id.y][id.z] = cell;
}

const CellUser &Chunk::get(const glm::uvec3 &id) const {
	return m_cells[id.x][id.y][id.z];
}

ChunkMesher *Chunk::get_mesher() {
	return m_mesher;
}

const ChunkMesher *Chunk::get_mesher() const {
	return m_mesher;
}

u32 Chunk::get_count() const {
	return m_count;
}
