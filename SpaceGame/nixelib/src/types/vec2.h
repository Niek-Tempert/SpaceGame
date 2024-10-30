#pragma once

template <typename TType>
struct vec2_t {
	union {
		struct {
			TType x, y;
		};
		TType data[2];
	};

	vec2_t() : x(0), y(0) {}

	vec2_t(TType x, TType y) : x(x), y(y) {}

	FORCEINLINE vec2_t &operator+=(const vec2_t &vec) {
		x += vec.x;
		y += vec.y;
		return *this;
	}
	FORCEINLINE vec2_t operator+(const vec2_t &vec) const {
		return { x + vec.x, y + vec.y };
	}
	FORCEINLINE vec2_t &operator-=(const vec2_t &vec) {
		x -= vec.x;
		y -= vec.y;
		return *this;
	}
	FORCEINLINE vec2_t operator-(const vec2_t &vec) const {
		return { x - vec.x, y - vec.y };
	}
	FORCEINLINE vec2_t &operator/=(const vec2_t &vec) {
		x /= vec.x;
		y /= vec.y;
		return *this;
	}
	FORCEINLINE vec2_t operator/(const vec2_t &vec) const {
		return { x / vec.x, y / vec.y };
	}
	FORCEINLINE vec2_t &operator*=(const vec2_t &vec) {
		x *= vec.x;
		y *= vec.y;
		return *this;
	}
	FORCEINLINE vec2_t operator*(const vec2_t &vec) const {
		return { x * vec.x, y * vec.y };
	}

	FORCEINLINE vec2_t &operator+=(TType scalar) {
		x += scalar;
		y += scalar;
		return *this;
	}
	FORCEINLINE vec2_t operator+(TType scalar) const {
		return { x + scalar, y + scalar };
	}
	FORCEINLINE vec2_t &operator-=(TType scalar) {
		x -= scalar;
		y -= scalar;
		return *this;
	}
	FORCEINLINE vec2_t operator-(TType scalar) const {
		return { x - scalar, y - scalar };
	}
	FORCEINLINE vec2_t &operator/=(TType scalar) {
		x /= scalar;
		y /= scalar;
		return *this;
	}
	FORCEINLINE vec2_t operator/(TType scalar) const {
		return { x / scalar, y / scalar };
	}
	FORCEINLINE vec2_t &operator*=(TType scalar) {
		x *= scalar;
		y *= scalar;
		return *this;
	}
	FORCEINLINE vec2_t operator*(TType scalar) const {
		return { x * scalar, y * scalar };
	}

	FORCEINLINE bool operator==(const vec2_t &vec) const {
		return x == vec.x && y == vec.y;
	}
	FORCEINLINE bool operator!=(const vec2_t &vec) const {
		return x != vec.x && y != vec.y;
	}
	FORCEINLINE bool operator<(const vec2_t &vec) const {
		if (x != vec.x) {
			return x < vec.x;
		}
		return y < vec.y;
	}
	FORCEINLINE bool operator<=(const vec2_t &vec) const {
		if (x != vec.x) {
			return x < vec.x;
		}
		return y <= vec.y;
	}
	FORCEINLINE bool operator>(const vec2_t &vec) const {
		if (x != vec.x) {
			return x > vec.x;
		}
		return y > vec.y;
	}
	FORCEINLINE bool operator>=(const vec2_t &vec) const {
		if (x != vec.x) {
			return x > vec.x;
		}
		return y >= vec.y;
	}
};

typedef vec2_t<f32> vec2f32;
typedef vec2_t<f64> vec2f64;

typedef vec2f32 vec2f;
typedef vec2f64 vec2d;

typedef vec2f32 vec2;
