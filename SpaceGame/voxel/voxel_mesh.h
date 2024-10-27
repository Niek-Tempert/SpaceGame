#pragma once

#include "nixelib/nixelib.h"
#include "rendering/renderable.h"

class Voxel;

class VoxelMesh : public MRenderable {
public:
	typedef vec3i chunk_id;
	typedef vec3i cell_id;
	
	void full_update(Voxel *voxel) const;
	void chunk_update(Voxel *voxel, const chunk_id &chunkid) const;
	void cell_update(Voxel *voxel, const cell_id &id) const;

	std::string get_vertex_shader() const override;
	std::string get_fragment_shader() const override;
	std::vector<vec3f> get_vertices() const override;
	std::vector<vec3f> get_normals() const override;
	std::vector<vec2f> get_uvs() const override;
	std::vector<u32> get_indices() const override;

private:
	std::vector<vec3f> vertices;
	std::vector<vec3f> normals;
	std::vector<vec2f> uvs;
	std::vector<u32> indices;
};
