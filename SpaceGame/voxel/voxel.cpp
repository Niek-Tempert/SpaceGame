#include "voxel.h"

#include "../utils/vec3i.h"

Voxel::~Voxel() {
	for (std::pair<const vec3i, VoxelChunk *> &pair : _chunks) {
		delete pair.second;
	}
}

BlockUser &Voxel::get(const vec3i &id) {
	vec3i chunkid = id_to_chunkid(id);
	const vec3i subid = id_to_subid(id);

	VoxelChunk *chunk;

	const auto it = _chunks.find(chunkid);
	if (it != _chunks.end()) {
		chunk = it->second;
	} else {
		chunk = new VoxelChunk();
		_chunks.insert({ chunkid, chunk });
	}

	return chunk->get(subid);
}

BlockUser *Voxel::get(const vec3i &id) const {
	const vec3i chunkid = id_to_chunkid(id);
	const vec3i subid = id_to_subid(id);

	const auto it = _chunks.find(chunkid);
	if (it == _chunks.end()) {
		return NULL;
	}
	return &it->second->get(subid);
}

vec3i Voxel::id_to_chunkid(const vec3i &id) {
	// TODO: Check if double precision helps prevent rounding errors
	return {
		nixemath::floor_to_i32((f32)id.x / VoxelChunk::size.x),
		nixemath::floor_to_i32((f32)id.y / VoxelChunk::size.y),
		nixemath::floor_to_i32((f32)id.z / VoxelChunk::size.z)
	};
}

vec3i Voxel::id_to_subid(const vec3i &id) {
	return {
		nixemath::floor_mod(id.x, VoxelChunk::size.x),
		nixemath::floor_mod(id.y, VoxelChunk::size.y),
		nixemath::floor_mod(id.z, VoxelChunk::size.z)
	};
}

vec3i Voxel::compound_id(const vec3i &chunkid, const vec3i &subid) {
	return {
		chunkid.x * VoxelChunk::size.x + subid.x,
		chunkid.y * VoxelChunk::size.y + subid.y,
		chunkid.z * VoxelChunk::size.z + subid.z
	};
}