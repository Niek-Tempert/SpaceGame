#pragma once

template <typename TType>
struct vec3i_t {
	union {
		struct {
			TType x;
			TType y;
			TType z;
		};
		TType data[3];
	};

	vec3i_t() : x(0), y(0), z(0) {}

	vec3i_t(TType x, TType y, TType z) : x(x), y(y), z(z) {}

	FORCEINLINE vec3i_t &operator+=(const vec3i_t &vec) {
		x += vec.x;
		y += vec.y;
		z += vec.z;
		return *this;
	}
	FORCEINLINE vec3i_t operator+(const vec3i_t &vec) const {
		return { x + vec.x, y + vec.y, z + vec.z };
	}
	FORCEINLINE vec3i_t &operator-=(const vec3i_t &vec) {
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		return *this;
	}
	FORCEINLINE vec3i_t operator-(const vec3i_t &vec) const {
		return { x - vec.x, y - vec.y, z - vec.z };
	}
	FORCEINLINE vec3i_t &operator/=(const vec3i_t &vec) {
		x /= vec.x;
		y /= vec.y;
		z /= vec.z;
		return *this;
	}
	FORCEINLINE vec3i_t operator/(const vec3i_t &vec) const {
		return { x / vec.x, y / vec.y, z / vec.z };
	}
	FORCEINLINE vec3i_t &operator*=(const vec3i_t &vec) {
		x *= vec.x;
		y *= vec.y;
		z *= vec.z;
		return *this;
	}
	FORCEINLINE vec3i_t operator*(const vec3i_t &vec) const {
		return { x * vec.x, y * vec.y, z * vec.z };
	}

	FORCEINLINE vec3i_t &operator+=(TType scalar) {
		x += scalar;
		y += scalar;
		z += scalar;
		return *this;
	}
	FORCEINLINE vec3i_t operator+(TType scalar) const {
		return { x + scalar, y + scalar, z + scalar };
	}
	FORCEINLINE vec3i_t &operator-=(TType scalar) {
		x -= scalar;
		y -= scalar;
		z -= scalar;
		return *this;
	}
	FORCEINLINE vec3i_t operator-(TType scalar) const {
		return { x - scalar, y - scalar, z - scalar };
	}
	FORCEINLINE vec3i_t &operator/=(TType scalar) {
		x /= scalar;
		y /= scalar;
		z /= scalar;
		return *this;
	}
	FORCEINLINE vec3i_t operator/(TType scalar) const {
		return { x / scalar, y / scalar, z / scalar };
	}
	FORCEINLINE vec3i_t &operator*=(TType scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}
	FORCEINLINE vec3i_t operator*(TType scalar) const {
		return { x * scalar, y * scalar, z * scalar };
	}

	FORCEINLINE bool operator==(const vec3i_t &vec) const {
		return x == vec.x && y == vec.y && z == vec.z;
	}
	FORCEINLINE bool operator!=(const vec3i_t &vec) const {
		return x != vec.x && y != vec.y && z != vec.z;
	}
	FORCEINLINE bool operator<(const vec3i_t &vec) const {
		if (x != vec.x) {
			return x < vec.x;
		}
		if (y != vec.y) {
			return y < vec.y;
		}
		return z < vec.z;
	}
	FORCEINLINE bool operator<=(const vec3i_t &vec) const {
		if (x != vec.x) {
			return x < vec.x;
		}
		if (y != vec.y) {
			return y < vec.y;
		}
		return z <= vec.z;
	}
	FORCEINLINE bool operator>(const vec3i_t &vec) const {
		if (x != vec.x) {
			return x > vec.x;
		}
		if (y != vec.y) {
			return y > vec.y;
		}
		return z > vec.z;
	}
	FORCEINLINE bool operator>=(const vec3i_t &vec) const {
		if (x != vec.x) {
			return x > vec.x;
		}
		if (y != vec.y) {
			return y > vec.y;
		}
		return z >= vec.z;
	}
};

typedef vec3i_t<i8> vec3i8;
typedef vec3i_t<i16> vec3i16;
typedef vec3i_t<i32> vec3i32;
typedef vec3i_t<i64> vec3i64;

typedef vec3i_t<u8> vec3u8;
typedef vec3i_t<u16> vec3u16;
typedef vec3i_t<u32> vec3u32;
typedef vec3i_t<u64> vec3u64;

typedef vec3i32 vec3i;
typedef vec3u32 vec3u;

