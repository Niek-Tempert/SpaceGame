#include "chunk_mesher.h"

#include "chunk.h"
#include "voxel.h"
#include "utils/mesh_consts.h"

#include <glm/ext/matrix_transform.hpp>

void ChunkMesher::update(const Voxel *voxel, const ChunkID &chunk_id) {
	_transform = glm::translate(glm::mat4(1.0f), glm::vec3(chunk_id.x * (i32)Chunk::size.x, chunk_id.y * (i32)Chunk::size.y, chunk_id.z * (i32)Chunk::size.z));
	this->_voxel = voxel;

	_vertices.clear();
	_colors.clear();
	_normals.clear();
	_uvs.clear();
	_indices.clear();

	const Chunk *chunk = voxel->get_chunks().at(chunk_id);

	for (u32 x = 0; x < Chunk::size.x; ++x) {
		for (u32 y = 0; y < Chunk::size.y; ++y) {
			for (u32 z = 0; z < Chunk::size.z; ++z) {
				const CellUser &cell = chunk->get({ x, y, z });
				if (!cell.type) {
					continue;
				}

				vec3i id = Voxel::compound_id(chunk_id, { x, y, z });
				vec3f col = hash_vec3f_to_vec3f(vec3f((float)chunk_id.x, (float)chunk_id.y, (float)chunk_id.z));
				for (int i = 0; i < 6; ++i) {
					auto &dir = mesh_consts::axis[i];
					auto *neighbor = voxel->get(id + dir);
					if (neighbor && neighbor->type) {
						continue;
					}

					for (u32 index : mesh_consts::face_indices) {
						_indices.push_back(index + (u32)_vertices.size());
					}

					for (const auto &vert : mesh_consts::cube_vertices[i]) {
						_vertices.emplace_back((float)x + vert.x, (float)y + vert.y, (float)z + vert.z);
						_colors.emplace_back(col);
					}

					for (u32 j = 0; j < (u32)std::size(*mesh_consts::cube_vertices); ++j) {
						_uvs.emplace_back(mesh_consts::face_uvs[j]);
						_normals.emplace_back(mesh_consts::cube_normals[i]);
					}
				}
			}
		}
	}

	setup();
}

glm::mat4x4 ChunkMesher::_get_transform() const {
	return _voxel->transform * _transform;
}

std::vector<vec3f> ChunkMesher::_get_vertices() const {
	return _vertices;
}

std::vector<vec3f> ChunkMesher::_get_colors() const {
	return _colors;
}

std::vector<vec3f> ChunkMesher::_get_normals() const {
	return _normals;
}

std::vector<vec2f> ChunkMesher::_get_uvs() const {
	return _uvs;
}

std::vector<u32> ChunkMesher::_get_indices() const {
	return _indices;
}

Shader ChunkMesher::_get_shader() const {
	return Shader::from_file("shaders/voxel.vert", "shaders/voxel.frag");
}