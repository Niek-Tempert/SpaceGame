#pragma once

#include "nixelib/nixelib.h"
#include "rendering/renderable.h"

#include <vector>

class Voxel;

class ChunkMesher : public MRenderable {
public:
	typedef vec3i ChunkID;
	typedef vec3i CellID;

	ChunkMesher() : _transform(glm::mat4(1.0f)), _voxel(NULL) {}

	void update(const Voxel *voxel, const ChunkID &chunk_id);

protected:
	glm::mat4x4 _get_transform() const override;
	std::vector<vec3f> _get_vertices() const override;
	std::vector<vec3f> _get_colors() const override;
	std::vector<vec3f> _get_normals() const override;
	std::vector<vec2f> _get_uvs() const override;
	std::vector<u32> _get_indices() const override;
	Shader _get_shader() const override;

	std::vector<vec3f> _vertices;
	std::vector<vec3f> _colors;
	std::vector<vec3f> _normals;
	std::vector<vec2f> _uvs;
	std::vector<u32> _indices;

	glm::mat4 _transform;
	const Voxel *_voxel;
};
