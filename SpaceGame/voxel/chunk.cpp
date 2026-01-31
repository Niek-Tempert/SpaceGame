#include "chunk.h"

#include "chunk_mesher.h"
#include "cell/cell_user.h"

Chunk::Chunk(): _mesher(new ChunkMesher()), _cells(), _count(0) {
}

void Chunk::set(const vec3u &id, const CellUser &cell) {
	if ((cell.type || cell.data)
		&& (!_cells[id.x][id.y][id.z].type && !_cells[id.x][id.y][id.z].data)) {
		_count++;
	} else if ((!cell.type && !cell.data)
		&& (_cells[id.x][id.y][id.z].type || _cells[id.x][id.y][id.z].data)) {
		_count--;
	}

	_cells[id.x][id.y][id.z] = cell;
}

const CellUser &Chunk::get(const vec3u &id) const {
	return _cells[id.x][id.y][id.z];
}

ChunkMesher *Chunk::get_mesher() {
	return _mesher;
}

const ChunkMesher *Chunk::get_mesher() const {
	return _mesher;
}

u32 Chunk::get_count() const {
	return _count;
}
