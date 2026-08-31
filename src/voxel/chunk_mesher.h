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
	glm::mat4x4 getTransform() const override;
	std::vector<glm::vec3> getVertices() const override;
	std::vector<glm::vec3> getColors() const override;
	std::vector<glm::vec3> getNormals() const override;
	std::vector<glm::vec2> getUVs() const override;
	std::vector<u32> getIndices() const override;
	GLuint getShader() const override;

	std::vector<glm::vec3> m_vertices;
	std::vector<glm::vec3> m_colors;
	std::vector<glm::vec3> m_normals;
	std::vector<glm::vec2> m_uvs;
	std::vector<u32> m_indices;

	glm::mat4 m_transform;
	const Voxel* m_voxel;
};
