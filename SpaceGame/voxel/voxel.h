#pragma once

#include "../utils/vec3i.h"
#include "../utils/array_3d.h"
#include "block/block_user.h"

#include <map>

typedef Array3D<BlockUser, 16, 16, 16> VoxelChunk;

typedef vec3i BlockID;
typedef vec3i ChunkID;
typedef vec3i SubID;

class Voxel {
public:
	~Voxel();

	BlockUser &get(const vec3i &id);
	BlockUser *get(const vec3i &id) const; // TODO: Make an optional reference / pointer type

private:
	std::map<vec3i, VoxelChunk *> _chunks;

	static vec3i id_to_chunkid(const BlockID &id);
	static vec3i id_to_subid(const BlockID &id);
	static vec3i compound_id(const ChunkID &chunkid, const SubID &subid);
};