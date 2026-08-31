#pragma once

#include "glad/glad.h"
#include "rendering/renderable.h"
#include <glm/vec3.hpp>

class Voxel;

class ChunkMesher : public MRenderable {
public:
	typedef glm::ivec3 ChunkID;
	typedef glm::ivec3 CellID;

	ChunkMesher() : _transform(glm::mat4(1.0f)), _voxel(NULL) {}

	void update(const Voxel *voxel, const ChunkID &chunk_id);

protected:
	glm::mat4x4 _get_transform() const override;
	std::vector<glm::vec3> _get_vertices() const override;
	std::vector<glm::vec3> _get_colors() const override;
	std::vector<glm::vec3> _get_normals() const override;
	std::vector<glm::vec2> _get_uvs() const override;
	std::vector<u32> _get_indices() const override;
	GLuint _get_shader() const override;

	std::vector<glm::vec3> _vertices;
	std::vector<glm::vec3> _colors;
	std::vector<glm::vec3> _normals;
	std::vector<glm::vec2> _uvs;
	std::vector<u32> _indices;

	glm::mat4 _transform;
	const Voxel *_voxel;
};
