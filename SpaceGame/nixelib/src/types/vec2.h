#pragma once

template <typename TType = f32>
struct vec2 {
	TType x;
	TType y;

	vec2() : x(0), y(0) {}

	vec2(TType x, TType y) : x(x), y(y) {}

	FORCEINLINE vec2 &operator+=(const vec2 &vec) {
		x += vec.x;
		y += vec.y;
		return *this;
	}
	FORCEINLINE vec2 operator+(const vec2 &vec) const {
		return { x + vec.x, y + vec.y };
	}
	FORCEINLINE vec2 &operator-=(const vec2 &vec) {
		x -= vec.x;
		y -= vec.y;
		return *this;
	}
	FORCEINLINE vec2 operator-(const vec2 &vec) const {
		return { x - vec.x, y - vec.y };
	}
	FORCEINLINE vec2 &operator/=(const vec2 &vec) {
		x /= vec.x;
		y /= vec.y;
		return *this;
	}
	FORCEINLINE vec2 operator/(const vec2 &vec) const {
		return { x / vec.x, y / vec.y };
	}
	FORCEINLINE vec2 &operator*=(const vec2 &vec) {
		x *= vec.x;
		y *= vec.y;
		return *this;
	}
	FORCEINLINE vec2 operator*(const vec2 &vec) const {
		return { x * vec.x, y * vec.y };
	}

	FORCEINLINE vec2 &operator+=(TType scalar) {
		x += scalar;
		y += scalar;
		return *this;
	}
	FORCEINLINE vec2 operator+(TType scalar) const {
		return { x + scalar, y + scalar };
	}
	FORCEINLINE vec2 &operator-=(TType scalar) {
		x -= scalar;
		y -= scalar;
		return *this;
	}
	FORCEINLINE vec2 operator-(TType scalar) const {
		return { x - scalar, y - scalar };
	}
	FORCEINLINE vec2 &operator/=(TType scalar) {
		x /= scalar;
		y /= scalar;
		return *this;
	}
	FORCEINLINE vec2 operator/(TType scalar) const {
		return { x / scalar, y / scalar };
	}
	FORCEINLINE vec2 &operator*=(TType scalar) {
		x *= scalar;
		y *= scalar;
		return *this;
	}
	FORCEINLINE vec2 operator*(TType scalar) const {
		return { x * scalar, y * scalar };
	}

	FORCEINLINE bool operator==(const vec2 &vec) const {
		return x == vec.x && y == vec.y;
	}
	FORCEINLINE bool operator!=(const vec2 &vec) const {
		return x != vec.x && y != vec.y;
	}
	FORCEINLINE bool operator<(const vec2 &vec) const {
		if (x != vec.x) {
			return x < vec.x;
		}
		return y < vec.y;
	}
	FORCEINLINE bool operator<=(const vec2 &vec) const {
		if (x != vec.x) {
			return x < vec.x;
		}
		return y <= vec.y;
	}
	FORCEINLINE bool operator>(const vec2 &vec) const {
		if (x != vec.x) {
			return x > vec.x;
		}
		return y > vec.y;
	}
	FORCEINLINE bool operator>=(const vec2 &vec) const {
		if (x != vec.x) {
			return x > vec.x;
		}
		return y >= vec.y;
	}
};

typedef vec2<f32> vec2f32;
typedef vec2<f64> vec2f64;

typedef vec2f32 vec2f;
typedef vec2f64 vec2d;
