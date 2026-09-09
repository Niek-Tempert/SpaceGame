#include "chunk.hpp"

#include "voxel.hpp"

Chunk::Chunk(const Voxel* voxel)
	: CameraProvider(voxel)
	, m_mesher(voxel)
	, m_cells()
	, m_count() {
}

void Chunk::set(const glm::uvec3 &id, const Block &cell) {
	if ((cell.type || cell.user)
		&& (!m_cells[id.x][id.y][id.z].type && !m_cells[id.x][id.y][id.z].user)) {
		m_count++;
	} else if ((!cell.type && !cell.user)
		&& (m_cells[id.x][id.y][id.z].type || m_cells[id.x][id.y][id.z].user)) {
		m_count--;
	}

	m_cells[id.x][id.y][id.z] = cell;
}

const Block& Chunk::get(const glm::uvec3 &id) const {
	return m_cells[id.x][id.y][id.z];
}

ChunkMesher* Chunk::getMesher() {
	return &m_mesher;
}

u32 Chunk::getCount() const {
	return m_count;
}
