#pragma once

#include "voxel_mesher.h"
#include "nixelib/nixelib.h"
#include "utils/array_3d.h"
#include "cell/user.h"

#include <map>

class Voxel {
public:
	typedef vec3i cell_id;
	typedef vec3i chunk_id;
	typedef vec3i sub_id;
	
	typedef Array3D<cell_user, 16, 16, 16> Chunk; // TODO: Mesh per chunk

	VoxelMesher *mesher;
	std::map<vec3i, Chunk *> _chunks;

	Voxel();
	virtual ~Voxel();

	cell_user &request(const vec3i &id);
	cell_user *get(const vec3i &id) const;

	static vec3i id_to_chunkid(const cell_id &id);
	static vec3i id_to_subid(const cell_id &cell_id);
	static vec3i compound_id(const chunk_id &chunk_id, const sub_id &sub_id);
};
