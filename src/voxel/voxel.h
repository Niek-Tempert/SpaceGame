#pragma once

#include "cell/cell_user.h"
#include "rendering/renderable.h"
#include <glm/vec3.hpp>

#include <map>

class Chunk;

struct ivec3_less {
    bool operator()(const glm::ivec3& a, const glm::ivec3& b) const noexcept {
        if (a.x != b.x) return a.x < b.x;
        if (a.y != b.y) return a.y < b.y;
        return a.z < b.z;
    }
};

struct RaycastResult {
	RaycastResult() : hit(false), id({ 0, 0, 0 }), normal({ 0, 0, 0 }), distance(0) {}
	RaycastResult(bool hit, const glm::ivec3 &id, const glm::ivec3 &normal, f32 distance) : hit(hit), id(id), normal(normal), distance(distance) {}
	
	bool hit;
	glm::ivec3 id;
	glm::ivec3 normal;
	f32 distance;
};

class Voxel : public IRenderable {
public:
	typedef glm::ivec3 CellID;
	typedef glm::ivec3 ChunkID;
	typedef glm::uvec3 SubID;

	glm::mat4 transform;

	Voxel();
	~Voxel() override;

	void set(const CellID &id, const CellUser &cell);
	const CellUser *get(const CellID &id) const;
	const std::map<glm::ivec3, Chunk*, ivec3_less> &get_chunks() const;

	void update(const CellID &id);
	void init() override;
	void render(RenderData *data) const override;

	RaycastResult raycast(const glm::vec3 &start, const glm::vec3 &direction, f32 max_distance);
	
	static ChunkID id_to_chunkid(const CellID &id);
	static SubID id_to_subid(const CellID &cell_id);
	static CellID compound_id(const ChunkID &chunk_id, const SubID &sub_id);

private:
	std::map<glm::ivec3, Chunk*, ivec3_less> chunks;
};
