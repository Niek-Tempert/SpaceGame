#pragma once

#include <stdexcept>

#include "nixelib/nixelib.h"

template <class TType, i64 SizeX, i64 SizeY, i64 SizeZ>
class Array3D {
public:
#define SIZE (SizeX * SizeY * SizeZ)
	static inline const vec3i size = { SizeX, SizeY, SizeZ };

	Array3D() = default;

	Array3D(const Array3D &source) {
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

	static bool is_valid(const vec3i &id) {
		return id.x >= 0 && id.x < SizeX
				&& id.y >= 0 && id.y < SizeY
				&& id.z >= 0 && id.z < SizeZ;
	}

	static int id_to_index(const vec3i &id) {
		return id.x + id.y * SizeX + id.z * SizeX * SizeY;
	}

	static vec3i index_to_id(int index) {
		int rect = SizeX * SizeY;
		return { index % SizeX, index % rect / SizeX, index / rect };
	}

private:
	TType _data[SIZE];
};

#undef SIZE