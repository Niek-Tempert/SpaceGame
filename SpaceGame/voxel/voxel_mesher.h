#pragma once

#include "nixelib/nixelib.h"

class Voxel;

class VoxelMesher {
public:
	typedef vec3i chunk_id;
	typedef vec3i cell_id;
	
	void full_update(Voxel *voxel) const;
	void chunk_update(Voxel *voxel, const chunk_id &chunkid) const;
	void cell_update(Voxel *voxel, const cell_id &id) const;
};
