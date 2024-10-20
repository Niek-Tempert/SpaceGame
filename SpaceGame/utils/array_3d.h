#pragma once

#include <array>

#include "vec3i.h"

#include <stdexcept>

template <class TType, i64 SIZE_X, i64 SIZE_Y, i64 SIZE_Z>
class Array3D {
public:
#define SIZE (SIZE_X * SIZE_Y * SIZE_Z)
	static inline const vec3i size = { SIZE_X, SIZE_Y, SIZE_Z };

	Array3D() = default;
	Array3D(const Array3D &source)  {
		this->_data = source._data;
	}

	TType &get(const vec3i &id) {
		if (!is_valid(id)) {
			throw new std::out_of_range("ID out of bounds");
		}
		return _data[id_to_index(id)];
	}
	const TType &get(const vec3i &id) const {
		if (!is_valid(id)) {
			throw new std::out_of_range("ID out of bounds");
		}
		return _data[id_to_index(id)];
	}

	TType &operator[](const vec3i &id) {
		return get(id);
	}
	const TType &operator[](const vec3i &id) const {
		return get(id);
	}

	bool is_valid(const vec3i &id) const {
		return id.x >= 0 && id.x < SIZE_X
			&& id.y >= 0 && id.y < SIZE_Y
			&& id.z >= 0 && id.z < SIZE_Z;
	}

private:
	TType _data[SIZE];

	int id_to_index(const vec3i &id) const{
		return id.x + id.y * SIZE_X + id.z * SIZE_X * SIZE_Y;
	}
	vec3i index_to_id(int index) const{
		int rect = SIZE_X * SIZE_Y;
		return { index % SIZE_X, index % rect / SIZE_X, index / rect };
	}
};
#undef SIZE
