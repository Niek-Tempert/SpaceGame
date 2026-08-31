#pragma once

#include "chunk_mesher.h"
#include "cell/cell_user.h"

#define CHUNK_SIZE 16u

class Chunk {
public:
	inline static const glm::uvec3 size = glm::uvec3(CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE);

	Chunk();
	
	void set(const glm::uvec3 &id, const CellUser &cell);
	const CellUser &get(const glm::uvec3 &id) const;

	ChunkMesher *get_mesher();
	const ChunkMesher *get_mesher() const;
	u32 get_count() const;

private:
	ChunkMesher* m_mesher;
	CellUser m_cells[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
	u32 m_count;
};

#undef CHUNK_SIZE
