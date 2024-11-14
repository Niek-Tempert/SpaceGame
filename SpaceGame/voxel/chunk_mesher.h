#pragma once

#include "nixelib/nixelib.h"
#include "rendering/renderable.h"

#include <vector>

class Voxel;

class ChunkMesher : public MRenderable {
public:
	typedef vec3i chunk_id;
	typedef vec3i cell_id;

	ChunkMesher() : _vertices(), _colors(), _normals(), _uvs(), _indices(), _voxel(nullptr) {}

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
	std::vector<vec3f> _vertices;
	std::vector<vec3f> _colors;
	std::vector<vec3f> _normals;
	std::vector<vec2f> _uvs;
	std::vector<u32> _indices;

	const Voxel *_voxel;
};