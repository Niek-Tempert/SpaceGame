#pragma once

#include "glad/glad.h"
#include "rendering/renderable.h"
#include <glm/vec3.hpp>

class Voxel;

class ChunkMesher : public MRenderable {
public:
	typedef glm::ivec3 ChunkID;
	typedef glm::ivec3 CellID;

	ChunkMesher() : m_transform(glm::mat4(1.0f)), m_voxel(NULL) {}

	void update(const Voxel *voxel, const ChunkID &chunk_id);

protected:
	glm::mat4x4 _get_transform() const override;
	std::vector<glm::vec3> _get_vertices() const override;
	std::vector<glm::vec3> _get_colors() const override;
	std::vector<glm::vec3> _get_normals() const override;
	std::vector<glm::vec2> _get_uvs() const override;
	std::vector<u32> _get_indices() const override;
	GLuint _get_shader() const override;

	std::vector<glm::vec3> m_vertices;
	std::vector<glm::vec3> m_colors;
	std::vector<glm::vec3> m_normals;
	std::vector<glm::vec2> m_uvs;
	std::vector<u32> m_indices;

	glm::mat4 m_transform;
	const Voxel* m_voxel;
};
