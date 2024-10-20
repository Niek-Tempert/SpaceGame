#pragma once

#include "../utils/vec3i.h"

class Voxel;

struct VoxelExplorer {
	VoxelExplorer() : voxel(nullptr), cursor({ 0, 0, 0 }) {};
	VoxelExplorer(Voxel *voxel, vec3i cursor) : voxel(voxel), cursor(cursor) {};

	Voxel *voxel;
	vec3i cursor;
};
