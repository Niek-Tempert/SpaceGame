#include "chunk.h"

#include "chunk_mesher.h"
#include "cell/cell_user.h"

void Chunk::set(const vec3u &id, const CellUser &cell) {
	if ((cell.type || cell.data)
		&& (!_cells[id].type && !_cells[id].data)) {
		_count++;
	} else if ((!cell.type && !cell.data)
		&& (_cells[id].type || _cells[id].data)) {
		_count--;
	}

	_cells[id] = cell;
}

const CellUser &Chunk::get(const vec3u &id) const {
	return _cells[id];
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
