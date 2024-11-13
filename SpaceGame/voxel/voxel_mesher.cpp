#include "voxel_mesher.h"

#include "voxel.h"
#include "utils/mesh_consts.h"

#include "nixelib/nixelib.h"

void VoxelMesher::full_update(const Voxel *voxel) {
	vertices.clear();
	colors.clear();
	normals.clear();
	uvs.clear();
	indices.clear();

	for (auto &pairs : voxel->_chunks) {
		for (int x = 0; x < Chunk::size.x; ++x) {
			for (int y = 0; y < Chunk::size.y; ++y) {
				for (int z = 0; z < Chunk::size.z; ++z) {
					const cell_user &cell = pairs.second->get({ x, y, z });
					if (!cell.type) {
						continue;
					}

					vec3i id = Voxel::compound_id(pairs.first, { x, y, z });
					vec3f col = hash_vec3f_to_vec3f(vec3f((float)id.x, (float)id.y, (float)id.z));
					for (int i = 0; i < 6; ++i) {
						auto &dir = mesh_consts::axis[i];
						auto *neighbor = voxel->get(id + dir);
						if (neighbor && neighbor->type) {
							continue;
						}

						for (u32 index : mesh_consts::face_indices) {
							indices.push_back(index + (u32)vertices.size());
						}

						for (const auto &vert : mesh_consts::cube_vertices[i]) {
							vertices.emplace_back((float)id.x + vert.x, (float)id.y + vert.y, (float)id.z + vert.z);
							colors.emplace_back(col);
						}

						for (u32 j = 0; j < (u32)std::size(*mesh_consts::cube_vertices); ++j) {
							uvs.emplace_back(mesh_consts::face_uvs[j]);
							normals.emplace_back(mesh_consts::cube_normals[i]);
						}
					}
				}
			}
		}
	}

	prepare();
}

const char *VoxelMesher::get_vertex_shader() const {
	return "shaders/voxel.vert";
}

const char *VoxelMesher::get_fragment_shader() const {
	return "shaders/voxel.frag";
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

std::vector<vec2f> VoxelMesher::get_uvs() const {
	return uvs;
}

std::vector<u32> VoxelMesher::get_indices() const {
	return indices;
}