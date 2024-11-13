#include "voxel.h"

#include "nixelib/nixelib.h"
#include "utils/mesh_consts.h"

#include <glm/ext/matrix_transform.hpp>

void ChunkMesher::update(const Voxel *voxel, const chunk_id &chunk_id) {
	transform = glm::translate(glm::mat4(1.0f), glm::vec3(chunk_id.x * Chunk::size.x, chunk_id.y * Chunk::size.y, chunk_id.z * Chunk::size.z));
	this->voxel = voxel;

	vertices.clear();
	colors.clear();
	normals.clear();
	uvs.clear();
	indices.clear();

	const Chunk *chunk = voxel->chunks.at(chunk_id);
	
	for (int x = 0; x < Chunk::size.x; ++x) {
		for (int y = 0; y < Chunk::size.y; ++y) {
			for (int z = 0; z < Chunk::size.z; ++z) {
				const cell_user &cell = chunk->get({ x, y, z });
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
						indices.push_back(index + (u32)vertices.size());
					}

					for (const auto &vert : mesh_consts::cube_vertices[i]) {
						vertices.emplace_back((float)x + vert.x, (float)y + vert.y, (float)z + vert.z);
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

	prepare();
}

glm::mat4x4 ChunkMesher::get_transform() const {
	return voxel->transform * transform;
}

const char * ChunkMesher::get_vertex_shader() const {
	return "shaders/voxel.vert";
}

const char * ChunkMesher::get_fragment_shader() const {
	return "shaders/voxel.frag";
}

std::vector<vec3f> ChunkMesher::get_vertices() const {
	return vertices;
}

std::vector<vec3f> ChunkMesher::get_colors() const {
	return colors;
}

std::vector<vec3f> ChunkMesher::get_normals() const {
	return normals;
}

std::vector<vec2f> ChunkMesher::get_uvs() const {
	return uvs;
}

std::vector<u32> ChunkMesher::get_indices() const {
	return indices;
}

void Chunk::set(const vec3i &id, const cell_user &cell) {
	if ((cell.type || cell.data)
		&& (!cells[id].type && !cells[id].data)) {
		count++;
	} else if ((!cell.type && !cell.data)
		&& (cells[id].type || cells[id].data)) {
		count--;
	}
		
	cells[id] = cell;
}

const cell_user & Chunk::get(const vec3i &id) const {
	return cells[id];
}

Voxel::Voxel() {
	transform = glm::mat4(1.0f);
}

Voxel::~Voxel() {
	for (std::pair<const vec3i, Chunk *> &pair : chunks) {
		delete pair.second;
	}
}

void Voxel::set(const vec3i &id, const cell_user &cell) {
	vec3i chunkid = id_to_chunkid(id);
	const vec3i subid = id_to_subid(id);

	Chunk *chunk;

	const auto it = chunks.find(chunkid);
	if (it != chunks.end()) {
		chunk = it->second;
	} else {
		chunk = new Chunk();
		chunks.insert({ chunkid, chunk });
	}

	chunk->set(subid, cell);
	if (chunk->count == 0) {
		delete chunk;
		chunks.erase(chunkid);
	}
}

const cell_user *Voxel::get(const vec3i &id) const {
	const vec3i chunkid = id_to_chunkid(id);
	const vec3i subid = id_to_subid(id);

	const auto it = chunks.find(chunkid);
	if (it == chunks.end()) {
		return NULL;
	}
	return &it->second->get(subid);
}

raycast_result Voxel::raycast(const vec3f &start, const vec3f &dir, f32 max_distance) {
	glm::mat4 transform = this->transform;
	glm::mat4 inv_transform = glm::inverse(transform);

	glm::vec3 scale;
	scale.x = glm::length(glm::vec3(transform[0])); // Basis vector X
	scale.y = glm::length(glm::vec3(transform[1])); // Basis vector Y
	scale.z = glm::length(glm::vec3(transform[2])); // Basis vector Z

	glm::vec3 direction = inv_transform * glm::vec4(dir.x, dir.y, dir.z, 0);
    direction = glm::normalize(direction);

    glm::vec3 scaled_dir = direction * max_distance;
    max_distance = glm::length(glm::vec3 {
        nixemath::save_divide(scaled_dir.x, scale.x),
        nixemath::save_divide(scaled_dir.y, scale.y),
        nixemath::save_divide(scaled_dir.z, scale.z)
    }); //scale distance from world scale to voxel scale

    glm::vec3 delta_dist = {
        glm::abs(1.0f / direction.x),
        glm::abs(1.0f / direction.y),
        glm::abs(1.0f / direction.z)
    };

    vec3i step = vec3i {
        direction.x < 0 ? -1 : 1,
        direction.y < 0 ? -1 : 1,
        direction.z < 0 ? -1 : 1
    };

    glm::vec3 voxel_space = inv_transform * glm::vec4(start.x, start.y, start.z, 1);

    vec3i map_pos = {
    	nixemath::floor_to_i32(voxel_space.x),
    	nixemath::floor_to_i32(voxel_space.y),
    	nixemath::floor_to_i32(voxel_space.z)
    };

    glm::vec3 side_dist = glm::vec3 (
        (direction.x < 0 ? voxel_space.x - map_pos.x : map_pos.x + 1 - voxel_space.x) * delta_dist.x,
        (direction.y < 0 ? voxel_space.y - map_pos.y : map_pos.y + 1 - voxel_space.y) * delta_dist.y,
        (direction.z < 0 ? voxel_space.z - map_pos.z : map_pos.z + 1 - voxel_space.z) * delta_dist.z
    );

    float ray_dist = 0;
    int side = -1;

    while (ray_dist < max_distance) {
		const cell_user *cell = get(map_pos);
		if (cell && cell->type) {
            vec3i face_dir;
            switch (side)
            {
                case 0:
                	if (step.x > 0) {
                		face_dir = {
                			-1, 0, 0
                		};
                	} else {
		                face_dir = {
		                	1, 0, 0
		                };
					}
					break;

                case 1:
                	if (step.y > 0) {
                		face_dir = {
                			0, -1, 0
                		};
                	} else {
                		face_dir = {
                			0, 1, 0
                		};
                	}
                    break;

                case 2:
                	if (step.z > 0) {
                		face_dir = {
                			0, 0, -1
                		};
                	} else {
                		face_dir = {
                			0, 0, 1
                		};
                	}
                    break;

                default:
                    face_dir = {
                	0, 0, 0
                    };
                    break;
            }

            ray_dist = glm::length(direction * ray_dist * scale); //scale distance from voxel scale to world scale

            return raycast_result (
            	true,
            	map_pos,
            	face_dir,
            	ray_dist
            );
        }

        if (side_dist.x < side_dist.y && side_dist.x < side_dist.z)
        {
            ray_dist = side_dist.x;
            side_dist.x += delta_dist.x;
            map_pos.x += step.x;
            side = 0;
        }
        else if (side_dist.y < side_dist.x && side_dist.y < side_dist.z)
        {
            ray_dist = side_dist.y;
            side_dist.y += delta_dist.y;
            map_pos.y += step.y;
            side = 1;
        }
        else
        {
            ray_dist = side_dist.z;
            side_dist.z += delta_dist.z;
            map_pos.z += step.z;
            side = 2;
        }
    }

    return {};
}

void Voxel::update(const vec3i &id) {
	const vec3i chunk_id = id_to_chunkid(id);
	const vec3i sub_id = id_to_subid(id);
	
	const auto it = chunks.find(chunk_id);
	if (it != chunks.end()) {
		it->second->mesher->update(this, chunk_id);
	}

	vec3i neighbor_id;
	if (sub_id.x <= 0) {
		neighbor_id = chunk_id;
		--neighbor_id.x;
		
		const auto it = chunks.find(neighbor_id);
		if (it != chunks.end()) {
			it->second->mesher->update(this, neighbor_id);
		}
	}
	
	if (sub_id.y <= 0) {
		neighbor_id = chunk_id;
		--neighbor_id.y;
		
		const auto it = chunks.find(neighbor_id);
		if (it != chunks.end()) {
			it->second->mesher->update(this, neighbor_id);
		}
	}
	
	if (sub_id.z <= 0) {
		neighbor_id = chunk_id;
		--neighbor_id.z;
		
		const auto it = chunks.find(neighbor_id);
		if (it != chunks.end()) {
			it->second->mesher->update(this, neighbor_id);
		}
	}

	if (sub_id.x >= Chunk::size.x - 1) {
		neighbor_id = chunk_id;
		++neighbor_id.x;
		
		const auto it = chunks.find(neighbor_id);
		if (it != chunks.end()) {
			it->second->mesher->update(this, neighbor_id);
		}
	}
	
	if (sub_id.y >= Chunk::size.y - 1) {
		neighbor_id = chunk_id;
		++neighbor_id.y;
		
		const auto it = chunks.find(neighbor_id);
		if (it != chunks.end()) {
			it->second->mesher->update(this, neighbor_id);
		}
	}
	
	if (sub_id.z >= Chunk::size.z - 1) {
		neighbor_id = chunk_id;
		++neighbor_id.z;
		
		const auto it = chunks.find(neighbor_id);
		if (it != chunks.end()) {
			it->second->mesher->update(this, neighbor_id);
		}
	}
}

vec3i Voxel::id_to_chunkid(const vec3i &id) {
	return {
		nixemath::floor_to_i32((f64)id.x / Chunk::size.x),
		nixemath::floor_to_i32((f64)id.y / Chunk::size.y),
		nixemath::floor_to_i32((f64)id.z / Chunk::size.z)
	};
}

vec3i Voxel::id_to_subid(const vec3i &cell_id) {
	return {
		nixemath::floor_mod(cell_id.x, Chunk::size.x),
		nixemath::floor_mod(cell_id.y, Chunk::size.y),
		nixemath::floor_mod(cell_id.z, Chunk::size.z)
	};
}

vec3i Voxel::compound_id(const vec3i &chunk_id, const vec3i &sub_id) {
	return {
		chunk_id.x * Chunk::size.x + sub_id.x,
		chunk_id.y * Chunk::size.y + sub_id.y,
		chunk_id.z * Chunk::size.z + sub_id.z
	};
}

void Voxel::prepare() {
	for (auto chunk : chunks) {
		chunk.second->mesher->update(this, chunk.first);
	}
}

void Voxel::render(draw_call_data *data) const {
	for (auto chunk : chunks) {
		chunk.second->mesher->render(data);
	}
}
