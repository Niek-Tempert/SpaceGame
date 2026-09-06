#pragma once

#include "voxel.h"
#include "chunk_mesher.h"
#include "block.hpp"

#define CHUNK_SIZE 16u

class Chunk : public CameraProvider {
public:
	inline static const glm::uvec3 size = glm::uvec3(CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE);

	Chunk(const Voxel* voxel);
	
	void set(const glm::uvec3 &id, const Block &cell);
	const Block &get(const glm::uvec3 &id) const;

	ChunkMesher *get_mesher();
	const ChunkMesher *get_mesher() const;
	u32 get_count() const;

private:
	ChunkMesher* m_mesher;
	Block m_cells[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
	u32 m_count;
};

#undef CHUNK_SIZE
