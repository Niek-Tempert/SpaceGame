#pragma once

#include "voxel_mesher.h"
#include "nixelib/nixelib.h"
#include "utils/array_3d.h"
#include "cell/user.h"

#include <map>

struct raycast_result {
	raycast_result() : hit(false), id({ 0, 0, 0 }), normal({ 0, 0, 0 }), distance(0) {}
	raycast_result(bool hit, const vec3i &id, const vec3i &normal, f32 distance) : hit(hit), id(id), normal(normal), distance(distance) {}
	
	bool hit;
	vec3i id;
	vec3i normal;
	f32 distance;
};

class Chunk {
public:
	void set(const vec3i &id, const cell_user &cell);
	const cell_user &get(const vec3i &id) const;

	Array3D<cell_user, 16, 16, 16> cells;
	u32 count;

	inline static const vec3i size = vec3i(16, 16, 16);
};

class Voxel {
public:
	typedef vec3i cell_id;
	typedef vec3i chunk_id;
	typedef vec3i sub_id;
	
	VoxelMesher *mesher;
	std::map<vec3i, Chunk *> _chunks;

	Voxel();
	virtual ~Voxel();

	void set(const vec3i &id, const cell_user &cell);
	const cell_user *get(const vec3i &id) const;

	raycast_result raycast(const vec3f &start, const vec3f &dir, f32 max_distance);

	static vec3i id_to_chunkid(const cell_id &id);
	static vec3i id_to_subid(const cell_id &cell_id);
	static vec3i compound_id(const chunk_id &chunk_id, const sub_id &sub_id);
};
