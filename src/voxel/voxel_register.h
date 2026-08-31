#pragma once

#include "glm/vec3.hpp"

class Voxel;

struct VoxelRegister {
	VoxelRegister() : voxel(nullptr), offset({ 0, 0, 0 }) {}
	VoxelRegister(Voxel *voxel, glm::ivec3 offset) : voxel(voxel), offset(offset) {}

	Voxel *voxel;
	glm::ivec3 offset;
};
