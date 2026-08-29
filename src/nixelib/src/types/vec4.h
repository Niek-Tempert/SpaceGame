#pragma once

template <typename TType>
struct vec4_t {
	union {
		struct {
			TType x, y, z, w;
		};
		TType data[3];
	};

	vec4_t() : x(0), y(0), z(0), w(0) {}

	vec4_t(TType x, TType y, TType z, TType w) : x(x), y(y), z(z), w(w) {}

	FORCEINLINE vec4_t &operator+=(const vec4_t &vec) {
		x += vec.x;
		y += vec.y;
		z += vec.z;
		w += vec.w;
		return *this;
	}
	FORCEINLINE vec4_t operator+(const vec4_t &vec) const {
		return { x + vec.x, y + vec.y, z + vec.z, w + vec.w };
	}
	FORCEINLINE vec4_t &operator-=(const vec4_t &vec) {
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		w -= vec.w;
		return *this;
	}
	FORCEINLINE vec4_t operator-(const vec4_t &vec) const {
		return { x - vec.x, y - vec.y, z - vec.z, w - vec.w };
	}
	FORCEINLINE vec4_t &operator/=(const vec4_t &vec) {
		x /= vec.x;
		y /= vec.y;
		z /= vec.z;
		w /= vec.w;
		return *this;
	}
	FORCEINLINE vec4_t operator/(const vec4_t &vec) const {
		return { x / vec.x, y / vec.y, z / vec.z, w / vec.w };
	}
	FORCEINLINE vec4_t &operator*=(const vec4_t &vec) {
		x *= vec.x;
		y *= vec.y;
		z *= vec.z;
		w *= vec.w;
		return *this;
	}
	FORCEINLINE vec4_t operator*(const vec4_t &vec) const {
		return { x * vec.x, y * vec.y, z * vec.z, w * vec.w };
	}

	FORCEINLINE vec4_t &operator+=(TType scalar) {
		x += scalar;
		y += scalar;
		z += scalar;
		w += scalar;
		return *this;
	}
	FORCEINLINE vec4_t operator+(TType scalar) const {
		return { x + scalar, y + scalar, z + scalar, w + scalar };
	}
	FORCEINLINE vec4_t &operator-=(TType scalar) {
		x -= scalar;
		y -= scalar;
		z -= scalar;
		w -= scalar;
		return *this;
	}
	FORCEINLINE vec4_t operator-(TType scalar) const {
		return { x - scalar, y - scalar, z - scalar, w - scalar };
	}
	FORCEINLINE vec4_t &operator/=(TType scalar) {
		x /= scalar;
		y /= scalar;
		z /= scalar;
		w /= scalar;
		return *this;
	}
	FORCEINLINE vec4_t operator/(TType scalar) const {
		return { x / scalar, y / scalar, z / scalar, w / scalar };
	}
	FORCEINLINE vec4_t &operator*=(TType scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
		w *= scalar;
		return *this;
	}
	FORCEINLINE vec4_t operator*(TType scalar) const {
		return { x * scalar, y * scalar, z * scalar, w * scalar };
	}

	FORCEINLINE bool operator==(const vec4_t &vec) const {
		return x == vec.x && y == vec.y && z == vec.z && w == vec.w;
	}
	FORCEINLINE bool operator!=(const vec4_t &vec) const {
		return x != vec.x && y != vec.y && z != vec.z && w != vec.w;
	}
	FORCEINLINE bool operator<(const vec4_t &vec) const {
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
	FORCEINLINE bool operator<=(const vec4_t &vec) const {
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
	FORCEINLINE bool operator>(const vec4_t &vec) const {
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
	FORCEINLINE bool operator>=(const vec4_t &vec) const {
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

typedef vec4_t<f32> vec4f32;
typedef vec4_t<f64> vec4f64;

typedef vec4f32 vec4f;
typedef vec4f64 vec4d;

typedef vec4f32 vec4;
