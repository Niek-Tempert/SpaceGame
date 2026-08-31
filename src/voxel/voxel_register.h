#pragma once

#include "glm/vec3.hpp"

class Voxel;

struct VoxelRegister {
	VoxelRegister() : m_voxel(nullptr), m_offset({ 0, 0, 0 }) {}
	VoxelRegister(Voxel *voxel, glm::ivec3 offset) : m_voxel(voxel), m_offset(offset) {}

	Voxel *m_voxel;
	glm::ivec3 m_offset;
};
