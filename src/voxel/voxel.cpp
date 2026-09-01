#include "voxel.h"

#include "chunk.h"

#include <rendering/mesh_consts.h>

#include <glm/ext/matrix_transform.hpp>
#include <common/math.h>

Voxel::Voxel() {
	m_transform = glm::mat4(1.0f);
}

Voxel::~Voxel() {
	for (std::pair<const glm::ivec3, Chunk *> &pair : chunks) {
		delete pair.second;
	}
}

void Voxel::set(const glm::ivec3 &id, const CellUser &cell) {
	glm::ivec3 chunkid = id_to_chunkid(id);
	const glm::uvec3 subid = id_to_subid(id);

	Chunk *chunk;

	const auto it = chunks.find(chunkid);
	if (it != chunks.end()) {
		chunk = it->second;
	} else {
		chunk = new Chunk();
		chunks.insert({ chunkid, chunk });
	}

	chunk->set(subid, cell);
	if (chunk->get_count() == 0) {
		delete chunk;
		chunks.erase(chunkid);
	}
}

const CellUser *Voxel::get(const glm::ivec3 &id) const {
	const glm::ivec3 chunkid = id_to_chunkid(id);
	const glm::uvec3 subid = id_to_subid(id);

	const auto it = chunks.find(chunkid);
	if (it == chunks.end()) {
		return NULL;
	}
	return &it->second->get(subid);
}

RaycastResult Voxel::raycast(const glm::vec3 &start, const glm::vec3 &direction, f32 max_distance) {
	glm::mat4 voxel_transform = this->m_transform;
	glm::mat4 voxel_transform_inv = glm::inverse(voxel_transform);

	glm::vec3 scale;
	scale.x = glm::length(glm::vec3(voxel_transform[0]));
	scale.y = glm::length(glm::vec3(voxel_transform[1]));
	scale.z = glm::length(glm::vec3(voxel_transform[2]));

	glm::vec3 local_direction = voxel_transform_inv * glm::vec4(direction.x, direction.y, direction.z, 0);
	local_direction = glm::normalize(local_direction);

	max_distance = glm::length(glm::vec3{
		save_divide(local_direction.x * max_distance, scale.x),
		save_divide(local_direction.y * max_distance, scale.y),
		save_divide(local_direction.z * max_distance, scale.z)
	}); //scale distance from world scale to voxel scale

	glm::vec3 delta_dist = {
		glm::abs(1.0f / local_direction.x),
		glm::abs(1.0f / local_direction.y),
		glm::abs(1.0f / local_direction.z)
	};

	glm::ivec3 step = glm::ivec3{
		local_direction.x < 0 ? -1 : 1,
		local_direction.y < 0 ? -1 : 1,
		local_direction.z < 0 ? -1 : 1
	};

	glm::vec3 voxel_space = voxel_transform_inv * glm::vec4(start.x, start.y, start.z, 1.0f);

	glm::ivec3 map_pos = {
		floor_to_i32(voxel_space.x),
		floor_to_i32(voxel_space.y),
		floor_to_i32(voxel_space.z)
	};

	glm::vec3 side_dist = glm::vec3(
			(local_direction.x < 0.0f ? voxel_space.x - (f32)map_pos.x : (f32)map_pos.x + 1.0f - voxel_space.x) * delta_dist.x,
			(local_direction.y < 0.0f ? voxel_space.y - (f32)map_pos.y : (f32)map_pos.y + 1.0f - voxel_space.y) * delta_dist.y,
			(local_direction.z < 0.0f ? voxel_space.z - (f32)map_pos.z : (f32)map_pos.z + 1.0f - voxel_space.z) * delta_dist.z
			);

	float ray_dist = 0;
	int side = -1;

	while (ray_dist < max_distance) {
		const CellUser *cell = get(map_pos);
		if (!cell || !cell->type) {
			if (side_dist.x < side_dist.y && side_dist.x < side_dist.z) {
				ray_dist = side_dist.x;
				side_dist.x += delta_dist.x;
				map_pos.x += step.x;
				side = 0;

				continue;
			}
			if (side_dist.y < side_dist.x && side_dist.y < side_dist.z) {
				ray_dist = side_dist.y;
				side_dist.y += delta_dist.y;
				map_pos.y += step.y;
				side = 1;

				continue;
			}

			ray_dist = side_dist.z;
			side_dist.z += delta_dist.z;
			map_pos.z += step.z;
			side = 2;
			continue;
		}

		glm::ivec3 face_dir;
		switch (side) {
			case 0:
				if (step.x > 0) {
					face_dir = { -1, 0, 0 };
				} else {
					face_dir = { 1, 0, 0 };
				}
				break;

			case 1:
				if (step.y > 0) {
					face_dir = { 0, -1, 0 };
				} else {
					face_dir = { 0, 1, 0 };
				}
				break;

			case 2:
				if (step.z > 0) {
					face_dir = { 0, 0, -1 };
				} else {
					face_dir = { 0, 0, 1 };
				}
				break;

			default:
				face_dir = {
					0, 0, 0
				};
				break;
		}

		ray_dist = glm::length(local_direction * ray_dist * scale); // Scale distance from voxel scale to world scale

		return {
			true,
			map_pos,
			face_dir,
			ray_dist
		};
	}

	return {};
}

void Voxel::update(const glm::ivec3 &id) {
	const glm::ivec3 chunk_id = id_to_chunkid(id);
	const glm::uvec3 sub_id = id_to_subid(id);

	const auto it = chunks.find(chunk_id);
	if (it != chunks.end()) {
		it->second->get_mesher()->update(this, chunk_id);
	}

	glm::ivec3 neighbor_id;
	if (sub_id.x <= 0) {
		neighbor_id = chunk_id;
		--neighbor_id.x;

		const auto it = chunks.find(neighbor_id);
		if (it != chunks.end()) {
			it->second->get_mesher()->update(this, neighbor_id);
		}
	}

	if (sub_id.y <= 0) {
		neighbor_id = chunk_id;
		--neighbor_id.y;

		const auto it = chunks.find(neighbor_id);
		if (it != chunks.end()) {
			it->second->get_mesher()->update(this, neighbor_id);
		}
	}

	if (sub_id.z <= 0) {
		neighbor_id = chunk_id;
		--neighbor_id.z;

		const auto it = chunks.find(neighbor_id);
		if (it != chunks.end()) {
			it->second->get_mesher()->update(this, neighbor_id);
		}
	}

	if (sub_id.x >= Chunk::size.x - 1) {
		neighbor_id = chunk_id;
		++neighbor_id.x;

		const auto it = chunks.find(neighbor_id);
		if (it != chunks.end()) {
			it->second->get_mesher()->update(this, neighbor_id);
		}
	}

	if (sub_id.y >= Chunk::size.y - 1) {
		neighbor_id = chunk_id;
		++neighbor_id.y;

		const auto it = chunks.find(neighbor_id);
		if (it != chunks.end()) {
			it->second->get_mesher()->update(this, neighbor_id);
		}
	}

	if (sub_id.z >= Chunk::size.z - 1) {
		neighbor_id = chunk_id;
		++neighbor_id.z;

		const auto it = chunks.find(neighbor_id);
		if (it != chunks.end()) {
			it->second->get_mesher()->update(this, neighbor_id);
		}
	}
}

glm::ivec3 Voxel::id_to_chunkid(const glm::ivec3 &id) {
	return {
		floor_to_i32((f64)id.x / Chunk::size.x),
		floor_to_i32((f64)id.y / Chunk::size.y),
		floor_to_i32((f64)id.z / Chunk::size.z)
	};
}

glm::uvec3 Voxel::id_to_subid(const glm::ivec3 &cell_id) {
	return {
		(u32)floor_mod(cell_id.x, (i32)Chunk::size.x),
		(u32)floor_mod(cell_id.y, (i32)Chunk::size.y),
		(u32)floor_mod(cell_id.z, (i32)Chunk::size.z)
	};
}

glm::ivec3 Voxel::compound_id(const glm::ivec3 &chunk_id, const glm::uvec3 &sub_id) {
	return {
		chunk_id.x * (i32)Chunk::size.x + (i32)sub_id.x,
		chunk_id.y * (i32)Chunk::size.y + (i32)sub_id.y,
		chunk_id.z * (i32)Chunk::size.z + (i32)sub_id.z
	};
}

const std::map<glm::ivec3, Chunk *, ivec3_less> &Voxel::get_chunks() const {
	return chunks;
}

void Voxel::rebuildMesh() {
	for (auto chunk : chunks) {
		chunk.second->get_mesher()->update(this, chunk.first);
	}
}

void Voxel::render(RenderData *data) const {
	for (auto chunk : chunks) {
		chunk.second->get_mesher()->render(data);
	}
}