#pragma once

template <typename TType = f32>
struct vec3 {
	TType x;
	TType y;
	TType z;

	vec3() : x(0), y(0), z(0) {}

	vec3(TType x, TType y, TType z) : x(x), y(y), z(z) {}

	FORCEINLINE vec3 &operator+=(const vec3 &vec) {
		x += vec.x;
		y += vec.y;
		z += vec.z;
		return *this;
	}
	FORCEINLINE vec3 operator+(const vec3 &vec) const {
		return { x + vec.x, y + vec.y, z + vec.z };
	}
	FORCEINLINE vec3 &operator-=(const vec3 &vec) {
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		return *this;
	}
	FORCEINLINE vec3 operator-(const vec3 &vec) const {
		return { x - vec.x, y - vec.y, z - vec.z };
	}
	FORCEINLINE vec3 &operator/=(const vec3 &vec) {
		x /= vec.x;
		y /= vec.y;
		z /= vec.z;
		return *this;
	}
	FORCEINLINE vec3 operator/(const vec3 &vec) const {
		return { x / vec.x, y / vec.y, z / vec.z };
	}
	FORCEINLINE vec3 &operator*=(const vec3 &vec) {
		x *= vec.x;
		y *= vec.y;
		z *= vec.z;
		return *this;
	}
	FORCEINLINE vec3 operator*(const vec3 &vec) const {
		return { x * vec.x, y * vec.y, z * vec.z };
	}

	FORCEINLINE vec3 &operator+=(TType scalar) {
		x += scalar;
		y += scalar;
		z += scalar;
		return *this;
	}
	FORCEINLINE vec3 operator+(TType scalar) const {
		return { x + scalar, y + scalar, z + scalar };
	}
	FORCEINLINE vec3 &operator-=(TType scalar) {
		x -= scalar;
		y -= scalar;
		z -= scalar;
		return *this;
	}
	FORCEINLINE vec3 operator-(TType scalar) const {
		return { x - scalar, y - scalar, z - scalar };
	}
	FORCEINLINE vec3 &operator/=(TType scalar) {
		x /= scalar;
		y /= scalar;
		z /= scalar;
		return *this;
	}
	FORCEINLINE vec3 operator/(TType scalar) const {
		return { x / scalar, y / scalar, z / scalar };
	}
	FORCEINLINE vec3 &operator*=(TType scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}
	FORCEINLINE vec3 operator*(TType scalar) const {
		return { x * scalar, y * scalar, z * scalar };
	}

	FORCEINLINE bool operator==(const vec3 &vec) const {
		return x == vec.x && y == vec.y && z == vec.z;
	}
	FORCEINLINE bool operator!=(const vec3 &vec) const {
		return x != vec.x && y != vec.y && z != vec.z;
	}
	FORCEINLINE bool operator<(const vec3 &vec) const {
		if (x != vec.x) {
			return x < vec.x;
		}
		if (y != vec.y) {
			return y < vec.y;
		}
		return z < vec.z;
	}
	FORCEINLINE bool operator<=(const vec3 &vec) const {
		if (x != vec.x) {
			return x < vec.x;
		}
		if (y != vec.y) {
			return y < vec.y;
		}
		return z <= vec.z;
	}
	FORCEINLINE bool operator>(const vec3 &vec) const {
		if (x != vec.x) {
			return x > vec.x;
		}
		if (y != vec.y) {
			return y > vec.y;
		}
		return z > vec.z;
	}
	FORCEINLINE bool operator>=(const vec3 &vec) const {
		if (x != vec.x) {
			return x > vec.x;
		}
		if (y != vec.y) {
			return y > vec.y;
		}
		return z >= vec.z;
	}
};

typedef vec3<f32> vec3f32;
typedef vec3<f64> vec3f64;

typedef vec3f32 vec3f;
typedef vec3f64 vec3d;
