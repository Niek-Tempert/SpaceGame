#pragma once

#include "ivoxel_mesher.h"

class Voxel;

class BlockMesher : public IVoxelMesher {
public:
	void full_update(Voxel *voxel) const override {};
	void chunk_update(Voxel *voxel, const ChunkID &chunkid) const override {};
	void block_update(Voxel *voxel, const BlockID &id) const override {};
};
