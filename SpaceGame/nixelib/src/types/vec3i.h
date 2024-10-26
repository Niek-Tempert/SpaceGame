#pragma once

template <typename TType = i32>
struct vec3i {
	TType x;
	TType y;
	TType z;

	vec3i() : x(0), y(0), z(0) {}

	vec3i(TType x, TType y, TType z) : x(x), y(y), z(z) {}

	FORCEINLINE vec3i &operator+=(const vec3i &vec) {
		x += vec.x;
		y += vec.y;
		z += vec.z;
		return *this;
	}
	FORCEINLINE vec3i operator+(const vec3i &vec) const {
		return { x + vec.x, y + vec.y, z + vec.z };
	}
	FORCEINLINE vec3i &operator-=(const vec3i &vec) {
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		return *this;
	}
	FORCEINLINE vec3i operator-(const vec3i &vec) const {
		return { x - vec.x, y - vec.y, z - vec.z };
	}
	FORCEINLINE vec3i &operator/=(const vec3i &vec) {
		x /= vec.x;
		y /= vec.y;
		z /= vec.z;
		return *this;
	}
	FORCEINLINE vec3i operator/(const vec3i &vec) const {
		return { x / vec.x, y / vec.y, z / vec.z };
	}
	FORCEINLINE vec3i &operator*=(const vec3i &vec) {
		x *= vec.x;
		y *= vec.y;
		z *= vec.z;
		return *this;
	}
	FORCEINLINE vec3i operator*(const vec3i &vec) const {
		return { x * vec.x, y * vec.y, z * vec.z };
	}

	FORCEINLINE vec3i &operator+=(TType scalar) {
		x += scalar;
		y += scalar;
		z += scalar;
		return *this;
	}
	FORCEINLINE vec3i operator+(TType scalar) const {
		return { x + scalar, y + scalar, z + scalar };
	}
	FORCEINLINE vec3i &operator-=(TType scalar) {
		x -= scalar;
		y -= scalar;
		z -= scalar;
		return *this;
	}
	FORCEINLINE vec3i operator-(TType scalar) const {
		return { x - scalar, y - scalar, z - scalar };
	}
	FORCEINLINE vec3i &operator/=(TType scalar) {
		x /= scalar;
		y /= scalar;
		z /= scalar;
		return *this;
	}
	FORCEINLINE vec3i operator/(TType scalar) const {
		return { x / scalar, y / scalar, z / scalar };
	}
	FORCEINLINE vec3i &operator*=(TType scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}
	FORCEINLINE vec3i operator*(TType scalar) const {
		return { x * scalar, y * scalar, z * scalar };
	}

	FORCEINLINE bool operator==(const vec3i &vec) const {
		return x == vec.x && y == vec.y && z == vec.z;
	}
	FORCEINLINE bool operator!=(const vec3i &vec) const {
		return x != vec.x && y != vec.y && z != vec.z;
	}
	FORCEINLINE bool operator<(const vec3i &vec) const {
		if (x != vec.x) {
			return x < vec.x;
		}
		if (y != vec.y) {
			return y < vec.y;
		}
		return z < vec.z;
	}
	FORCEINLINE bool operator<=(const vec3i &vec) const {
		if (x != vec.x) {
			return x < vec.x;
		}
		if (y != vec.y) {
			return y < vec.y;
		}
		return z <= vec.z;
	}
	FORCEINLINE bool operator>(const vec3i &vec) const {
		if (x != vec.x) {
			return x > vec.x;
		}
		if (y != vec.y) {
			return y > vec.y;
		}
		return z > vec.z;
	}
	FORCEINLINE bool operator>=(const vec3i &vec) const {
		if (x != vec.x) {
			return x > vec.x;
		}
		if (y != vec.y) {
			return y > vec.y;
		}
		return z >= vec.z;
	}
};

typedef vec3i<i8> vec3i8;
typedef vec3i<i16> vec3i16;
typedef vec3i<i32> vec3i32;
typedef vec3i<i64> vec3i64;

typedef vec3i<u8> vec3u8;
typedef vec3i<u16> vec3u16;
typedef vec3i<u32> vec3u32;
typedef vec3i<u64> vec3u64;

typedef vec3u32 vec3u;