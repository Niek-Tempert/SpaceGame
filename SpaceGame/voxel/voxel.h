#pragma once

#include "nixelib/nixelib.h"
#include "utils/array_3d.h"
#include "cell/user.h"
#include "rendering/renderable.h"

#include <map>

class Voxel;

struct raycast_result {
	raycast_result() : hit(false), id({ 0, 0, 0 }), normal({ 0, 0, 0 }), distance(0) {}
	raycast_result(bool hit, const vec3i &id, const vec3i &normal, f32 distance) : hit(hit), id(id), normal(normal), distance(distance) {}
	
	bool hit;
	vec3i id;
	vec3i normal;
	f32 distance;
};

class ChunkMesher : public MRenderable {
public:
	typedef vec3i chunk_id;
	typedef vec3i cell_id;

	void update(const Voxel *voxel, const chunk_id &chunk_id);

	glm::mat4x4 get_transform() const override;
	const char *get_vertex_shader() const override;
	const char *get_fragment_shader() const override;
	std::vector<vec3f> get_vertices() const override;
	std::vector<vec3f> get_colors() const override;
	std::vector<vec3f> get_normals() const override;
	std::vector<vec2f> get_uvs() const override;
	std::vector<u32> get_indices() const override;

private:
	std::vector<vec3f> vertices;
	std::vector<vec3f> colors;
	std::vector<vec3f> normals;
	std::vector<vec2f> uvs;
	std::vector<u32> indices;

	const Voxel *voxel;
};

#define CHUNK_SIZE 16

class Chunk {
public:
	inline static const vec3i size = vec3i(CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE);
	
	void set(const vec3i &id, const cell_user &cell);
	const cell_user &get(const vec3i &id) const;

	ChunkMesher *mesher = new ChunkMesher();
	Array3D<cell_user, CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE> cells;
	u32 count;

};

class Voxel : public IRenderable {
public:
	typedef vec3i cell_id;
	typedef vec3i chunk_id;
	typedef vec3i sub_id;

	glm::mat4 transform;
	std::map<vec3i, Chunk *> chunks;

	Voxel();
	~Voxel() override;

	void set(const vec3i &id, const cell_user &cell);
	const cell_user *get(const vec3i &id) const;

	raycast_result raycast(const vec3f &start, const vec3f &dir, f32 max_distance);

	void update(const vec3i &id);
	void prepare() override;
	void render(draw_call_data *data) const override;

	static vec3i id_to_chunkid(const cell_id &id);
	static vec3i id_to_subid(const cell_id &cell_id);
	static vec3i compound_id(const chunk_id &chunk_id, const sub_id &sub_id);
};
