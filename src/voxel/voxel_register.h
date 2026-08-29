#pragma once

#include "nixelib/nixelib.h"

class Voxel;

struct VoxelRegister {
	VoxelRegister() : voxel(nullptr), offset({ 0, 0, 0 }) {}
	VoxelRegister(Voxel *voxel, vec3i offset) : voxel(voxel), offset(offset) {}

	Voxel *voxel;
	vec3i offset;
};
