#include "chunk_mesher.hpp"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <common/helpers.h>
#include <common/glutils.h>
#include <glm/ext/matrix_transform.hpp>

#include <rendering/mesh_consts.hpp>

#include "voxel.hpp"
#include "chunk.hpp"

ChunkMesher::ChunkMesher(const Voxel* parent) : 
	Renderable(parent)
	, m_transform(glm::mat4(1.0f))
	, m_voxel(NULL)
	, m_texture() {
	i32 width, height, nrChannels;
	u8* data = stbi_load(IMAGE_PATH "white_wool.png", &width, &height, &nrChannels, 0);
	if (!data) {
		std::cout << "Failed to load texture\n";
		return;
	}
	
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}

ChunkMesher::~ChunkMesher() {
	glDeleteTextures(1, &m_texture);
}

void ChunkMesher::update(const Voxel *voxel, const ChunkID &chunk_id) {
	m_transform = glm::translate(glm::mat4(1.0f), glm::vec3(chunk_id.x * (i32)Chunk::size.x, chunk_id.y * (i32)Chunk::size.y, chunk_id.z * (i32)Chunk::size.z));
	this->m_voxel = voxel;

	m_vertices.clear();
	m_colors.clear();
	m_normals.clear();
	m_uvs.clear();
	m_indices.clear();

	const Chunk *chunk = voxel->getChunks().at(chunk_id);

	for (u32 x = 0; x < Chunk::size.x; ++x) {
		for (u32 y = 0; y < Chunk::size.y; ++y) {
			for (u32 z = 0; z < Chunk::size.z; ++z) {
				const Block &cell = chunk->get({ x, y, z });
				if (!cell.type) continue;

				glm::ivec3 id = Voxel::compoundID(chunk_id, { x, y, z });
				glm::vec3 col = glm::vec3((f32)id.x, (f32)id.y, (f32)id.z);
				for (u32 i = 0; i < 6; ++i) {
					auto &dir = MeshConsts::axis[i];
					auto *neighbor = voxel->get(id + dir);
					if (neighbor && neighbor->type) continue;

					for (u32 index : MeshConsts::faceIndices) {
						m_indices.push_back(index + (u32)m_vertices.size());
					}

					for (const auto &vert : MeshConsts::cubeVerts[i]) {
						m_vertices.emplace_back((f32)x + vert.x, (f32)y + vert.y, (f32)z + vert.z);
						m_colors.emplace_back(col);
					}

					for (u32 j = 0; j < (u32)std::size(*MeshConsts::cubeVerts); ++j) {
						m_uvs.emplace_back(MeshConsts::faceUVs[j]);
						m_normals.emplace_back(MeshConsts::cubeNormals[i]);
					}
				}
			}
		}
	}

	remesh();
}

glm::mat4 ChunkMesher::getTransform() const {
	return m_voxel->getTransform() * m_transform;
}

std::vector<glm::vec3> ChunkMesher::getVertices() const {
	return m_vertices;
}

std::vector<glm::vec3> ChunkMesher::getColors() const {
	return m_colors;
}

std::vector<glm::vec3> ChunkMesher::getNormals() const {
	return m_normals;
}

std::vector<glm::vec2> ChunkMesher::getUVs() const {
	return m_uvs;
}

std::vector<u32> ChunkMesher::getIndices() const {
	return m_indices;
}

GLuint ChunkMesher::getShader() const {
	GLuint shader = 0;
	if (shaderLoadVF(&shader, SHADER_PATH "voxel.vert", SHADER_PATH "voxel.frag")) throw;
	return shader;
}
