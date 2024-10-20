#pragma once

#include "voxel_block.h"

struct BlockUser {
	VoxelBlock* block = nullptr;
	void *data = nullptr;
};