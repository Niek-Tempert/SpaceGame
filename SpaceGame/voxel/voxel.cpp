#include "voxel.h"

#include "nixelib/nixelib.h"

Voxel::~Voxel() {
	for (std::pair<const vec3i, Chunk *> &pair : _chunks) {
		delete pair.second;
	}
}

cell_user &Voxel::get(const vec3i &id) {
	vec3i chunkid = id_to_chunkid(id);
	const vec3i subid = id_to_subid(id);

	Chunk *chunk;

	const auto it = _chunks.find(chunkid);
	if (it != _chunks.end()) {
		chunk = it->second;
	} else {
		chunk = new Chunk();
		_chunks.insert({ chunkid, chunk });
	}

	return chunk->get(subid);
}

cell_user *Voxel::get(const vec3i &id) const {
	const vec3i chunkid = id_to_chunkid(id);
	const vec3i subid = id_to_subid(id);

	const auto it = _chunks.find(chunkid);
	if (it == _chunks.end()) {
		return NULL;
	}
	return &it->second->get(subid);
}

vec3i Voxel::id_to_chunkid(const vec3i &id) {
	return {
		nixemath::floor_to_i32((f64)id.x / Chunk::size.x),
		nixemath::floor_to_i32((f64)id.y / Chunk::size.y),
		nixemath::floor_to_i32((f64)id.z / Chunk::size.z)
	};
}

vec3i Voxel::id_to_subid(const vec3i &cell_id) {
	return {
		nixemath::floor_mod(cell_id.x, Chunk::size.x),
		nixemath::floor_mod(cell_id.y, Chunk::size.y),
		nixemath::floor_mod(cell_id.z, Chunk::size.z)
	};
}

vec3i Voxel::compound_id(const vec3i &chunk_id, const vec3i &sub_id) {
	return {
		chunk_id.x * Chunk::size.x + sub_id.x,
		chunk_id.y * Chunk::size.y + sub_id.y,
		chunk_id.z * Chunk::size.z + sub_id.z
	};
}