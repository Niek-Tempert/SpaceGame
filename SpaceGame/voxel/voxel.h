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

	BlockUser &get_user(const vec3i &id);
	BlockUser *get_user(const vec3i &id) const; // TODO: Make an optional reference / pointer type

private:
	//TODO: Move this into a separate class?
	//TODO: Custom hashmap for chunk specific seeding
	std::map<vec3i, VoxelChunk *> _chunks;

	vec3i id_to_chunkid(const BlockID &id) const;
	vec3i id_to_subid(const BlockID &id) const;
	vec3i compound_id(const ChunkID &chunkid, const SubID &subid) const;
};
