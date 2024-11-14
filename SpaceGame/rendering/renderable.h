#pragma once

#include "nixelib/nixelib.h"

#include <vector>
#include <glm/mat4x4.hpp>

enum class RenderType {
	triangles,
	indexed,
	lines
};

struct DrawCallData {
	glm::mat4 view;
	glm::mat4 proj;

	vec2u resolution;
};

struct RenderObject {
	u32 vao;
	u32 program;
	
	i32 model_loc;
	i32 view_loc;
	i32 proj_loc;
	i32 mvp_loc;
	
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
	virtual void render(DrawCallData* data) const = 0;
};

class MRenderable : public IRenderable {
public:
	~MRenderable() override;
	glm::mat4 transform = glm::mat4(1.0f);
	bool visible = true;

	void prepare() override;
	void render(DrawCallData* data) const override;

protected:
	virtual RenderType get_render_type() const { return RenderType::indexed; }
	virtual void set_gl_state() const;

	virtual glm::mat4x4 get_transform() const { return transform; }
	
	virtual const char *get_vertex_shader() const { return {}; }
	virtual const char *get_fragment_shader() const { return {}; }
	virtual const char *get_texture() const { return {}; }
	
	virtual std::vector<vec3f> get_vertices() const { return {}; }
	virtual std::vector<vec3f> get_colors() const { return {}; }
	virtual std::vector<vec3f> get_normals() const { return {}; }
	virtual std::vector<vec2f> get_uvs() const { return {}; }
	virtual std::vector<u32> get_indices() const { return {}; }

	RenderObject* object;
};