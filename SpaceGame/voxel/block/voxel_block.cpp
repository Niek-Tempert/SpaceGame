#include "voxel_block.h"

const IVoxelMesher &VoxelBlock::get_mesher() const {
	return *_mesher;
}