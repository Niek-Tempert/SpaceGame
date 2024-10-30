#pragma once

template <typename TType>
struct vec2i_t {
	union {
		struct {
			TType x, y;
		};
		TType data[2];
	};

	vec2i_t() : x(0), y(0) {}

	vec2i_t(TType x, TType y) : x(x), y(y) {}

	FORCEINLINE vec2i_t &operator+=(const vec2i_t &vec) {
		x += vec.x;
		y += vec.y;
		return *this;
	}
	FORCEINLINE vec2i_t operator+(const vec2i_t &vec) const {
		return { x + vec.x, y + vec.y };
	}
	FORCEINLINE vec2i_t &operator-=(const vec2i_t &vec) {
		x -= vec.x;
		y -= vec.y;
		return *this;
	}
	FORCEINLINE vec2i_t operator-(const vec2i_t &vec) const {
		return { x - vec.x, y - vec.y };
	}
	FORCEINLINE vec2i_t &operator/=(const vec2i_t &vec) {
		x /= vec.x;
		y /= vec.y;
		return *this;
	}
	FORCEINLINE vec2i_t operator/(const vec2i_t &vec) const {
		return { x / vec.x, y / vec.y };
	}
	FORCEINLINE vec2i_t &operator*=(const vec2i_t &vec) {
		x *= vec.x;
		y *= vec.y;
		return *this;
	}
	FORCEINLINE vec2i_t operator*(const vec2i_t &vec) const {
		return { x * vec.x, y * vec.y };
	}

	FORCEINLINE vec2i_t &operator+=(TType scalar) {
		x += scalar;
		y += scalar;
		return *this;
	}
	FORCEINLINE vec2i_t operator+(TType scalar) const {
		return { x + scalar, y + scalar };
	}
	FORCEINLINE vec2i_t &operator-=(TType scalar) {
		x -= scalar;
		y -= scalar;
		return *this;
	}
	FORCEINLINE vec2i_t operator-(TType scalar) const {
		return { x - scalar, y - scalar };
	}
	FORCEINLINE vec2i_t &operator/=(TType scalar) {
		x /= scalar;
		y /= scalar;
		return *this;
	}
	FORCEINLINE vec2i_t operator/(TType scalar) const {
		return { x / scalar, y / scalar };
	}
	FORCEINLINE vec2i_t &operator*=(TType scalar) {
		x *= scalar;
		y *= scalar;
		return *this;
	}
	FORCEINLINE vec2i_t operator*(TType scalar) const {
		return { x * scalar, y * scalar };
	}

	FORCEINLINE bool operator==(const vec2i_t &vec) const {
		return x == vec.x && y == vec.y;
	}
	FORCEINLINE bool operator!=(const vec2i_t &vec) const {
		return x != vec.x && y != vec.y;
	}
	FORCEINLINE bool operator<(const vec2i_t &vec) const {
		if (x != vec.x) {
			return x < vec.x;
		}
		return y < vec.y;
	}
	FORCEINLINE bool operator<=(const vec2i_t &vec) const {
		if (x != vec.x) {
			return x < vec.x;
		}
		return y <= vec.y;
	}
	FORCEINLINE bool operator>(const vec2i_t &vec) const {
		if (x != vec.x) {
			return x > vec.x;
		}
		return y > vec.y;
	}
	FORCEINLINE bool operator>=(const vec2i_t &vec) const {
		if (x != vec.x) {
			return x > vec.x;
		}
		return y >= vec.y;
	}
};

typedef vec2i_t<i8> vec2i8;
typedef vec2i_t<i16> vec2i16;
typedef vec2i_t<i32> vec2i32;
typedef vec2i_t<i64> vec2i64;

typedef vec2i_t<u8> vec2u8;
typedef vec2i_t<u16> vec2u16;
typedef vec2i_t<u32> vec2u32;
typedef vec2i_t<u64> vec2u64;

typedef vec2i32 vec2i;
typedef vec2u32 vec2u;

