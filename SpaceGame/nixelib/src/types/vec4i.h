#pragma once

template <typename TType = i32>
struct vec4i {
	TType x;
	TType y;
	TType z;
	TType w;

	vec4i() : x(0), y(0), z(0), w(0) {}

	vec4i(TType x, TType y, TType z, TType w) : x(x), y(y), z(z), w(w) {}

	FORCEINLINE vec4i &operator+=(const vec4i &vec) {
		x += vec.x;
		y += vec.y;
		z += vec.z;
		w += vec.w;
		return *this;
	}
	FORCEINLINE vec4i operator+(const vec4i &vec) const {
		return { x + vec.x, y + vec.y, z + vec.z, w + vec.w };
	}
	FORCEINLINE vec4i &operator-=(const vec4i &vec) {
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		w -= vec.w;
		return *this;
	}
	FORCEINLINE vec4i operator-(const vec4i &vec) const {
		return { x - vec.x, y - vec.y, z - vec.z, w - vec.w };
	}
	FORCEINLINE vec4i &operator/=(const vec4i &vec) {
		x /= vec.x;
		y /= vec.y;
		z /= vec.z;
		w /= vec.w;
		return *this;
	}
	FORCEINLINE vec4i operator/(const vec4i &vec) const {
		return { x / vec.x, y / vec.y, z / vec.z, w / vec.w };
	}
	FORCEINLINE vec4i &operator*=(const vec4i &vec) {
		x *= vec.x;
		y *= vec.y;
		z *= vec.z;
		w *= vec.w;
		return *this;
	}
	FORCEINLINE vec4i operator*(const vec4i &vec) const {
		return { x * vec.x, y * vec.y, z * vec.z, w * vec.w };
	}

	FORCEINLINE vec4i &operator+=(TType scalar) {
		x += scalar;
		y += scalar;
		z += scalar;
		w += scalar;
		return *this;
	}
	FORCEINLINE vec4i operator+(TType scalar) const {
		return { x + scalar, y + scalar, z + scalar, w + scalar };
	}
	FORCEINLINE vec4i &operator-=(TType scalar) {
		x -= scalar;
		y -= scalar;
		z -= scalar;
		w -= scalar;
		return *this;
	}
	FORCEINLINE vec4i operator-(TType scalar) const {
		return { x - scalar, y - scalar, z - scalar, w - scalar };
	}
	FORCEINLINE vec4i &operator/=(TType scalar) {
		x /= scalar;
		y /= scalar;
		z /= scalar;
		w /= scalar;
		return *this;
	}
	FORCEINLINE vec4i operator/(TType scalar) const {
		return { x / scalar, y / scalar, z / scalar, w / scalar };
	}
	FORCEINLINE vec4i &operator*=(TType scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
		w *= scalar;
		return *this;
	}
	FORCEINLINE vec4i operator*(TType scalar) const {
		return { x * scalar, y * scalar, z * scalar, w * scalar };
	}

	FORCEINLINE bool operator==(const vec4i &vec) const {
		return x == vec.x && y == vec.y && z == vec.z && w == vec.w;
	}
	FORCEINLINE bool operator!=(const vec4i &vec) const {
		return x != vec.x && y != vec.y && z != vec.z && w != vec.w;
	}
	FORCEINLINE bool operator<(const vec4i &vec) const {
		if (x != vec.x) {
			return x < vec.x;
		}
		if (y != vec.y) {
			return y < vec.y;
		}
		if (z != vec.z) {
			return z < vec.z;
		}
		return w < vec.w;
	}
	FORCEINLINE bool operator<=(const vec4i &vec) const {
		if (x != vec.x) {
			return x < vec.x;
		}
		if (y != vec.y) {
			return y < vec.y;
		}
		if (z != vec.z) {
			return z < vec.z;
		}
		return w <= vec.w;
	}
	FORCEINLINE bool operator>(const vec4i &vec) const {
		if (x != vec.x) {
			return x > vec.x;
		}
		if (y != vec.y) {
			return y > vec.y;
		}
		if (z != vec.z) {
			return z > vec.z;
		}
		return w > vec.w;
	}
	FORCEINLINE bool operator>=(const vec4i &vec) const {
		if (x != vec.x) {
			return x > vec.x;
		}
		if (y != vec.y) {
			return y > vec.y;
		}
		if (z != vec.z) {
			return z > vec.z;
		}
		return w >= vec.w;
	}
};

typedef vec4i<i8> vec4i8;
typedef vec4i<i16> vec4i16;
typedef vec4i<i32> vec4i32;
typedef vec4i<i64> vec4i64;

typedef vec4i<u8> vec4u8;
typedef vec4i<u16> vec4u16;
typedef vec4i<u32> vec4u32;
typedef vec4i<u64> vec4u64;

typedef vec4u32 vec4u;