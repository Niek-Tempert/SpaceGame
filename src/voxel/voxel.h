#pragma once

#include "nixelib/nixelib.h"
#include "cell/cell_user.h"
#include "rendering/renderable.h"

#include <map>

class Chunk;

struct RaycastResult {
	RaycastResult() : hit(false), id({ 0, 0, 0 }), normal({ 0, 0, 0 }), distance(0) {}
	RaycastResult(bool hit, const vec3i &id, const vec3i &normal, f32 distance) : hit(hit), id(id), normal(normal), distance(distance) {}
	
	bool hit;
	vec3i id;
	vec3i normal;
	f32 distance;
};

class Voxel : public IRenderable {
public:
	typedef vec3i CellID;
	typedef vec3i ChunkID;
	typedef vec3u SubID;

	glm::mat4 transform;

	Voxel();
	~Voxel() override;

	void set(const CellID &id, const CellUser &cell);
	const CellUser *get(const CellID &id) const;
	const std::map<vec3i, Chunk *> &get_chunks() const;

	void update(const CellID &id);
	void init() override;
	void render(RenderData *data) const override;

	RaycastResult raycast(const vec3f &start, const vec3f &direction, f32 max_distance);
	
	static ChunkID id_to_chunkid(const CellID &id);
	static SubID id_to_subid(const CellID &cell_id);
	static CellID compound_id(const ChunkID &chunk_id, const SubID &sub_id);

private:
	std::map<vec3i, Chunk *> chunks;
};
