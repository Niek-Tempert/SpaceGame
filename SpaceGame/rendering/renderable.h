#pragma once

#include "nixelib/nixelib.h"

#include <string>
#include <vector>
#include <glm/mat4x4.hpp>

enum class render_type {
	triangle,
	indexed,
};

struct render_proxy {
	u32 program;
	u32 vao;
	u32 mvp_location;
	u32 vert_count;
	u32 index_count;
};

class IRenderable {
public:
	virtual void prepare() = 0;
	virtual void render(glm::mat4 view, glm::mat4 proj) const = 0;
};

class MRenderable : public IRenderable {
public:
	MRenderable() : transform(glm::mat4(1.0f)) {}
	virtual ~MRenderable() = default;

	glm::mat4 transform;

	void prepare() override;
	void render(glm::mat4 view, glm::mat4 proj) const override;

protected:
	virtual render_type get_render_type() const { return render_type::indexed; }

	virtual glm::mat4x4 get_transform() const { return transform; }
	virtual const std::string get_vertex_shader() const { return {}; }
	virtual const std::string get_fragment_shader() const { return {}; }
	virtual const std::vector<vec3f> get_vertices() const { return {}; }
	virtual const std::vector<vec3f> get_colors() const { return {}; }
	virtual const std::vector<vec3f> get_normals() const { return {}; }
	virtual const std::vector<vec2f> get_uvs() const { return {}; }
	virtual const std::vector<u32> get_indices() const { return {}; }

	render_proxy proxy;
};