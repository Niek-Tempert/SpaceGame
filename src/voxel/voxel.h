#pragma once

#include "block.hpp"
#include "rendering/renderable.hpp"
#include "providers/camera_provider.hpp"
#include "engine/scene.hpp"
#include <glm/vec3.hpp>

#include <map>

class Chunk;
struct ivec3Less {
	bool operator()(const glm::ivec3 &a, const glm::ivec3 &b) const noexcept;
};

typedef glm::ivec3 CellID;
typedef glm::ivec3 ChunkID;
typedef glm::uvec3 SubID;

struct RaycastResult {
	RaycastResult() : hit(false), id({ 0, 0, 0 }), normal({ 0, 0, 0 }), distance(0) {}
	RaycastResult(bool hit, const glm::ivec3 &id, const glm::ivec3 &normal, f32 distance) : hit(hit), id(id), normal(normal), distance(distance) {}
	
	bool hit;
	glm::ivec3 id;
	glm::ivec3 normal;
	f32 distance;
};

class Voxel 
	: public IRenderable
	, public CameraProvider {
public:
	Voxel(const Scene* parent);
	~Voxel();

	void set(const CellID &id, const Block &cell);
	const Block *get(const CellID &id) const;
	const std::map<glm::ivec3, Chunk*, ivec3Less> &getChunks() const;
	const glm::mat4& getTransform() const;
	void setTransform(const glm::mat4& transform);

	void update(const CellID &id);
	void rebuildMesh();
	void render() const override;

	RaycastResult raycast(const glm::vec3 &start, const glm::vec3 &direction, f32 max);
	
	static ChunkID id2chunkID(const CellID &id);
	static SubID id2subID(const CellID &cell_id);
	static CellID compoundID(const ChunkID &chunk_id, const SubID &sub_id);

private:
	std::map<glm::ivec3, Chunk*, ivec3Less> m_chunks;
	glm::mat4 m_transform;
};
