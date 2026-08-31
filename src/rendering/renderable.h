#pragma once

#include "glad/glad.h"

#include <vector>
#include <glm/mat4x4.hpp>
#include <common/types.h>

struct RenderData {
	glm::mat4 view;
	glm::mat4 proj;

	glm::uvec2 resolution;
};

struct RenderObject {
	u32 vao;
	GLuint shader;

	i32 vertex_count;
	i32 index_count;

	i32 pos_buffer;
	i32 col_buffer;
	i32 norm_buffer;
	i32 uv_buffer;
	i32 index_buffer;

	u32 texture_buffer;
};

class IRenderable {
public:
	virtual ~IRenderable() = default;
	
	virtual void init() = 0;
	virtual void render(RenderData *data) const = 0;
};

class MRenderable : public IRenderable {
public:
	MRenderable() : _render_object(NULL) {}
	~MRenderable() override;
	
	void init() override;
	void render(RenderData *data) const final;

protected:
	virtual void _set_gl_state() const;

	virtual glm::mat4x4 _get_transform() const { return glm::mat4(1.0f); }
	virtual std::vector<glm::vec3> _get_vertices() const { return {}; }
	virtual std::vector<glm::vec3> _get_colors() const { return {}; }
	virtual std::vector<glm::vec3> _get_normals() const { return {}; }
	virtual std::vector<glm::vec2> _get_uvs() const { return {}; }
	virtual std::vector<u32> _get_indices() const { return {}; }
	virtual GLuint _get_shader() const { return 0; }

	virtual void _before_render(RenderData *data) const;
	virtual void _render() const;

	RenderObject *_render_object;
};
