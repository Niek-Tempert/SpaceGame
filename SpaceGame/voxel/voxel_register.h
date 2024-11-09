#pragma once

#include "nixelib/nixelib.h"

class Voxel;

struct voxel_register {
	voxel_register() : voxel(nullptr), offset({ 0, 0, 0 }) {}
	voxel_register(Voxel *voxel, vec3i offset) : voxel(voxel), offset(offset) {}

	Voxel *voxel;
	vec3i offset;
};
