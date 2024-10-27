#pragma once

template <typename TType>
struct vec3_t {
	union {
		struct {
			TType x;
			TType y;
			TType z;
		};
		TType data[3];
	};

	vec3_t() : x(0), y(0), z(0) {}

	vec3_t(TType x, TType y, TType z) : x(x), y(y), z(z) {}

	FORCEINLINE vec3_t &operator+=(const vec3_t &vec) {
		x += vec.x;
		y += vec.y;
		z += vec.z;
		return *this;
	}
	FORCEINLINE vec3_t operator+(const vec3_t &vec) const {
		return { x + vec.x, y + vec.y, z + vec.z };
	}
	FORCEINLINE vec3_t &operator-=(const vec3_t &vec) {
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		return *this;
	}
	FORCEINLINE vec3_t operator-(const vec3_t &vec) const {
		return { x - vec.x, y - vec.y, z - vec.z };
	}
	FORCEINLINE vec3_t &operator/=(const vec3_t &vec) {
		x /= vec.x;
		y /= vec.y;
		z /= vec.z;
		return *this;
	}
	FORCEINLINE vec3_t operator/(const vec3_t &vec) const {
		return { x / vec.x, y / vec.y, z / vec.z };
	}
	FORCEINLINE vec3_t &operator*=(const vec3_t &vec) {
		x *= vec.x;
		y *= vec.y;
		z *= vec.z;
		return *this;
	}
	FORCEINLINE vec3_t operator*(const vec3_t &vec) const {
		return { x * vec.x, y * vec.y, z * vec.z };
	}

	FORCEINLINE vec3_t &operator+=(TType scalar) {
		x += scalar;
		y += scalar;
		z += scalar;
		return *this;
	}
	FORCEINLINE vec3_t operator+(TType scalar) const {
		return { x + scalar, y + scalar, z + scalar };
	}
	FORCEINLINE vec3_t &operator-=(TType scalar) {
		x -= scalar;
		y -= scalar;
		z -= scalar;
		return *this;
	}
	FORCEINLINE vec3_t operator-(TType scalar) const {
		return { x - scalar, y - scalar, z - scalar };
	}
	FORCEINLINE vec3_t &operator/=(TType scalar) {
		x /= scalar;
		y /= scalar;
		z /= scalar;
		return *this;
	}
	FORCEINLINE vec3_t operator/(TType scalar) const {
		return { x / scalar, y / scalar, z / scalar };
	}
	FORCEINLINE vec3_t &operator*=(TType scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}
	FORCEINLINE vec3_t operator*(TType scalar) const {
		return { x * scalar, y * scalar, z * scalar };
	}

	FORCEINLINE bool operator==(const vec3_t &vec) const {
		return x == vec.x && y == vec.y && z == vec.z;
	}
	FORCEINLINE bool operator!=(const vec3_t &vec) const {
		return x != vec.x && y != vec.y && z != vec.z;
	}
	FORCEINLINE bool operator<(const vec3_t &vec) const {
		if (x != vec.x) {
			return x < vec.x;
		}
		if (y != vec.y) {
			return y < vec.y;
		}
		return z < vec.z;
	}
	FORCEINLINE bool operator<=(const vec3_t &vec) const {
		if (x != vec.x) {
			return x < vec.x;
		}
		if (y != vec.y) {
			return y < vec.y;
		}
		return z <= vec.z;
	}
	FORCEINLINE bool operator>(const vec3_t &vec) const {
		if (x != vec.x) {
			return x > vec.x;
		}
		if (y != vec.y) {
			return y > vec.y;
		}
		return z > vec.z;
	}
	FORCEINLINE bool operator>=(const vec3_t &vec) const {
		if (x != vec.x) {
			return x > vec.x;
		}
		if (y != vec.y) {
			return y > vec.y;
		}
		return z >= vec.z;
	}
};

typedef vec3_t<f32> vec3f32;
typedef vec3_t<f64> vec3f64;

typedef vec3f32 vec3f;
typedef vec3f64 vec3d;

typedef vec3f32 vec3;
