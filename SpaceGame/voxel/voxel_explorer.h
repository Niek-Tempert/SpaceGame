#pragma once

#include "nixelib/nixelib.h"

class Voxel;

struct voxel_explorer {
	voxel_explorer() : voxel(nullptr), cursor({ 0, 0, 0 }) {}
	voxel_explorer(Voxel *voxel, vec3i cursor) : voxel(voxel), cursor(cursor) {}

	Voxel *voxel;
	vec3i cursor;
};
