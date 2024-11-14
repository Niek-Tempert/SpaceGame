#pragma once

#include "nixelib/nixelib.h"

template <typename TType>
class Iterator {
public:
	Iterator(TType *data) : _data(data) {}

	TType &operator*() {
		return *_data;
	}

	const TType &operator*() const {
		return _data;
	}

	Iterator &operator++() {
		++_data;
		return *this;
	}

	Iterator &operator--() {
		--_data;
		return *this;
	}

	bool operator==(const Iterator &other) const {
		return _data == other._data;
	}

	bool operator!=(const Iterator &other) const {
		return _data != other._data;
	}
	
private:
	TType* _data;
};

#define CHUNK_SIZE (SizeX * SizeY * SizeZ)

template <typename TType, u64 SizeX, u64 SizeY, u64 SizeZ>
class Array3D {
public:
	inline static const vec3i size = { SizeX, SizeY, SizeZ };

	using Iterator = Iterator<TType>;

	Array3D() = default;

	Array3D(const Array3D &source) {
		this->_data = source._data;
	}

	FORCEINLINE TType &get(const vec3u &id) {
		return _data[id_to_index(id)];
	}

	FORCEINLINE const TType &get(const vec3u &id) const {
		return _data[id_to_index(id)];
	}

	FORCEINLINE TType &operator[](const vec3u &id) {
		return get(id);
	}

	FORCEINLINE const TType &operator[](const vec3u &id) const {
		return get(id);
	}

	PURE FORCEINLINE static int id_to_index(const vec3u &id) {
		return id.x + id.y * SizeX + id.z * SizeX * SizeY;
	}

	PURE FORCEINLINE static vec3i index_to_id(int index) {
		int rect = SizeX * SizeY;
		return { index % SizeX, index % rect / SizeX, index / rect };
	}

	PURE Iterator begin() {
		TType* begin = _data;
		return Iterator(begin);
	}

	PURE Iterator end() {
		TType* end = _data + CHUNK_SIZE;
		return Iterator(end);
	}

	PURE const Iterator begin() const {
		TType* begin = _data;
		return Iterator(begin);
	}

	PURE const Iterator end() const {
		TType* end = _data + CHUNK_SIZE;
		return Iterator(end);
	}

private:
	TType _data[CHUNK_SIZE];
};

#undef CHUNK_SIZE
