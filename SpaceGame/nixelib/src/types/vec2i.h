#pragma once

template <typename TType = i32>
struct vec2i {
	TType x;
	TType y;

	vec2i() : x(0), y(0) {}

	vec2i(TType x, TType y) : x(x), y(y) {}

	FORCEINLINE vec2i &operator+=(const vec2i &vec) {
		x += vec.x;
		y += vec.y;
		return *this;
	}
	FORCEINLINE vec2i operator+(const vec2i &vec) const {
		return { x + vec.x, y + vec.y };
	}
	FORCEINLINE vec2i &operator-=(const vec2i &vec) {
		x -= vec.x;
		y -= vec.y;
		return *this;
	}
	FORCEINLINE vec2i operator-(const vec2i &vec) const {
		return { x - vec.x, y - vec.y };
	}
	FORCEINLINE vec2i &operator/=(const vec2i &vec) {
		x /= vec.x;
		y /= vec.y;
		return *this;
	}
	FORCEINLINE vec2i operator/(const vec2i &vec) const {
		return { x / vec.x, y / vec.y };
	}
	FORCEINLINE vec2i &operator*=(const vec2i &vec) {
		x *= vec.x;
		y *= vec.y;
		return *this;
	}
	FORCEINLINE vec2i operator*(const vec2i &vec) const {
		return { x * vec.x, y * vec.y };
	}

	FORCEINLINE vec2i &operator+=(TType scalar) {
		x += scalar;
		y += scalar;
		return *this;
	}
	FORCEINLINE vec2i operator+(TType scalar) const {
		return { x + scalar, y + scalar };
	}
	FORCEINLINE vec2i &operator-=(TType scalar) {
		x -= scalar;
		y -= scalar;
		return *this;
	}
	FORCEINLINE vec2i operator-(TType scalar) const {
		return { x - scalar, y - scalar };
	}
	FORCEINLINE vec2i &operator/=(TType scalar) {
		x /= scalar;
		y /= scalar;
		return *this;
	}
	FORCEINLINE vec2i operator/(TType scalar) const {
		return { x / scalar, y / scalar };
	}
	FORCEINLINE vec2i &operator*=(TType scalar) {
		x *= scalar;
		y *= scalar;
		return *this;
	}
	FORCEINLINE vec2i operator*(TType scalar) const {
		return { x * scalar, y * scalar };
	}

	FORCEINLINE bool operator==(const vec2i &vec) const {
		return x == vec.x && y == vec.y;
	}
	FORCEINLINE bool operator!=(const vec2i &vec) const {
		return x != vec.x && y != vec.y;
	}
	FORCEINLINE bool operator<(const vec2i &vec) const {
		if (x != vec.x) {
			return x < vec.x;
		}
		return y < vec.y;
	}
	FORCEINLINE bool operator<=(const vec2i &vec) const {
		if (x != vec.x) {
			return x < vec.x;
		}
		return y <= vec.y;
	}
	FORCEINLINE bool operator>(const vec2i &vec) const {
		if (x != vec.x) {
			return x > vec.x;
		}
		return y > vec.y;
	}
	FORCEINLINE bool operator>=(const vec2i &vec) const {
		if (x != vec.x) {
			return x > vec.x;
		}
		return y >= vec.y;
	}
};

typedef vec2i<i8> vec2i8;
typedef vec2i<i16> vec2i16;
typedef vec2i<i32> vec2i32;
typedef vec2i<i64> vec2i64;

typedef vec2i<u8> vec2u8;
typedef vec2i<u16> vec2u16;
typedef vec2i<u32> vec2u32;
typedef vec2i<u64> vec2u64;

typedef vec2u32 vec2u;

