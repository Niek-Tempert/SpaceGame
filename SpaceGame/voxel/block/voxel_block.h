#pragma once

class IVoxelMesher;

class VoxelBlock {
public:
	// Name
	// Base Type?
	// Data manager
	// Block mesher / meshing type enum

	const IVoxelMesher &get_mesher() const;

private:
	const IVoxelMesher *_mesher;
};