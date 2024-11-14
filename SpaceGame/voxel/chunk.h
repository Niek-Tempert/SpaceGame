#pragma once

#include "chunk_mesher.h"
#include "cell/cell_user.h"
#include "nixelib/nixelib.h"
#include "rendering/renderable.h"
#include "utils/array_3d.h"

#define CHUNK_SIZE 16u

class Chunk {
public:
	inline static const vec3u size = vec3u(CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE);

	Chunk() : _mesher(new ChunkMesher()), _count(0) {}
	
	void set(const vec3u &id, const CellUser &cell);
	const CellUser &get(const vec3u &id) const;

	ChunkMesher *get_mesher();
	const ChunkMesher *get_mesher() const;
	u32 get_count() const;

private:
	ChunkMesher *_mesher;
	Array3D<CellUser, CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE> _cells;
	u32 _count;
};

#undef CHUNK_SIZE
