#include "voxel_mesh.h"

#include <string>

inline std::string VoxelMesh::get_vertex_shader() const {
	return "shaders/vertex/voxel.glsl";
}

inline std::string VoxelMesh::get_fragment_shader() const {
	return "shaders/fragment/voxel.glsl";
}

inline std::vector<vec3f> VoxelMesh::get_vertices() const {
	return vertices;
}

inline std::vector<vec3f> VoxelMesh::get_normals() const {
	return normals;
}

inline std::vector<vec2f> VoxelMesh::get_uvs() const {
	return uvs;
}

inline std::vector<u32> VoxelMesh::get_indices() const {
	return indices;
}