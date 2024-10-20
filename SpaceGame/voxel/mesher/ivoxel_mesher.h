#pragma once

#include "../../utils/vec3i.h"

class Voxel;

typedef vec3i ChunkID;
typedef vec3i BlockID;

class IVoxelMesher {
public:
	virtual ~IVoxelMesher() = default;

	virtual void full_update(Voxel *voxel) const = 0;
	virtual void chunk_update(Voxel *voxel, const ChunkID &chunkid) const = 0;
	virtual void block_update(Voxel *voxel, const BlockID &id) const = 0;

protected:
	static void _bind_methods();
};
