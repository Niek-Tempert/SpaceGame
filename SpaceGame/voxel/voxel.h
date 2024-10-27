#pragma once

#include "voxel_mesh.h"
#include "nixelib/nixelib.h"
#include "utils/array_3d.h"
#include "cell/user.h"

#include <map>

class Voxel {
public:
	typedef vec3i cell_id;
	typedef vec3i chunk_id;
	typedef vec3i sub_id;
	
	typedef Array3D<cell_user, 16, 16, 16> Chunk;

	VoxelMesh *mesh;
	
	~Voxel();

	cell_user &get(const vec3i &id);
	cell_user *get(const vec3i &id) const; // TODO: Make an optional reference / pointer type

	static vec3i id_to_chunkid(const cell_id &id);
	static vec3i id_to_subid(const cell_id &cell_id);
	static vec3i compound_id(const chunk_id &chunk_id, const sub_id &sub_id);

private:
	std::map<vec3i, Chunk *> _chunks;
};
