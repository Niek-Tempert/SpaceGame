#include "voxel_mesher.h"

#include "voxel.h"
#include "utils/mesh_consts.h"

#include <string>
#include <glm/ext/matrix_transform.hpp>

void VoxelMesher::full_update(Voxel *voxel) {
	vertices.clear();
	indices.clear();

	for (auto &pairs : voxel->_chunks) {
		for (int x = 0; x < Voxel::Chunk::size.x; ++x) {
			for (int y = 0; y < Voxel::Chunk::size.y; ++y) {
				for (int z = 0; z < Voxel::Chunk::size.z; ++z) {
					cell_user &cell = pairs.second->get({ x, y, z });
					if (!cell.data) {
						continue;
					}
					
					vec3i ID = Voxel::compound_id(pairs.first, { x, y, z });
					for (int i = 0; i < 6; ++i) {
						auto& dir = mesh_consts::cube_directions[i];
						auto* neighbor = voxel->get(ID + dir);
						if (neighbor && neighbor->data) {
							continue;
						}
						
						for (u32 index : mesh_consts::cube_indices) {
							indices.push_back(index + (u32)vertices.size());
						}
						
						for (const auto& vert : mesh_consts::cube_vertices[i]) {
							vertices.emplace_back((float)ID.x + vert.x, (float)ID.y + vert.y, (float)ID.z + vert.z);
							colors.emplace_back(vert.x, vert.y, vert.z);
						}

						for (int j = 0; j < std::size(mesh_consts::cube_vertices[i]); ++j) {
							normals.emplace_back(mesh_consts::cube_normals[i]);
						}
					}
				}
			}
		}
	}
}

std::string VoxelMesher::get_vertex_shader() const {
	return "shaders/vertex/voxel.glsl";
}

std::string VoxelMesher::get_fragment_shader() const {
	return "shaders/fragment/voxel.glsl";
}

std::vector<vec3f> VoxelMesher::get_vertices() const {
	return vertices;
}

std::vector<vec3f> VoxelMesher::get_colors() const {
	return colors;
}

std::vector<vec3f> VoxelMesher::get_normals() const {
	return normals;
}

std::vector<u32> VoxelMesher::get_indices() const {
	return indices;
}