#pragma once

#include "nixelib/nixelib.h"

#include <string>
#include <vector>
#include <glm/mat4x4.hpp>

enum class render_type {
	triangle,
	indexed,
};

struct render_object {
	u32 vao;
	u32 program;
	i32 mvp_loc;
	i32 vert_shader;
	i32 frag_shader;
	i32 vertex_count;
	i32 index_count;
	i32 pos_buffer;
	i32 col_buffer;
	i32 norm_buffer;
	i32 uv_buffer;
	i32 index_buffer;
};

class IRenderable {
public:
	virtual ~IRenderable() = default;
	virtual void prepare() = 0;
	virtual void render(glm::mat4 vp) const = 0;
};

class MRenderable : public IRenderable {
public:
	~MRenderable() override;
	glm::mat4 transform = glm::mat4(1.0f);

	void prepare() override;
	void render(glm::mat4 vp) const override;

protected:
	virtual render_type get_render_type() const { return render_type::indexed; }

	virtual glm::mat4x4 get_transform() const { return transform; }
	virtual std::string get_vertex_shader() const { return {}; }
	virtual std::string get_fragment_shader() const { return {}; }
	virtual std::vector<vec3f> get_vertices() const { return {}; }
	virtual std::vector<vec3f> get_colors() const { return {}; }
	virtual std::vector<vec3f> get_normals() const { return {}; }
	virtual std::vector<vec2f> get_uvs() const { return {}; }
	virtual std::vector<u32> get_indices() const { return {}; }

	render_object* object;
};