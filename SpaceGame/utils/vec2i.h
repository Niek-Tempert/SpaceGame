#pragma once

#include "../nixelib/nixelib.h"

struct vec2i {
	i32 x;
	i32 y;

	vec2i() : x(0), y(0) {}
	vec2i(i32 x, i32 y) : x(x), y(y) {}

	vec2i &operator+=(const vec2i &vec);
	vec2i operator+(const vec2i &vec) const;
	vec2i &operator-=(const vec2i &vec);
	vec2i operator-(const vec2i &vec) const;
	vec2i &operator/=(const vec2i &vec);
	vec2i operator/(const vec2i &vec) const;
	vec2i &operator*=(const vec2i &vec);
	vec2i operator*(const vec2i &vec) const;

	vec2i &operator+=(i32 val);
	vec2i operator+(i32 val) const;
	vec2i &operator-=(i32 val);
	vec2i operator-(i32 val) const;
	vec2i &operator/=(i32 val);
	vec2i operator/(i32 val) const;
	vec2i &operator*=(i32 val);
	vec2i operator*(i32 val) const;

	bool operator==(const vec2i &vec) const;
	bool operator!=(const vec2i &vec) const;
	bool operator<(const vec2i &vec) const;
	bool operator<=(const vec2i &vec) const;
	bool operator>(const vec2i &vec) const;
	bool operator>=(const vec2i &vec) const;
};

inline vec2i &vec2i::operator+=(const vec2i &vec) {
	x += vec.x;
	y += vec.y;
	return *this;
}

inline vec2i &vec2i::operator-=(const vec2i &vec) {
	x -= vec.x;
	y -= vec.y;
	return *this;
}

inline vec2i &vec2i::operator/=(const vec2i &vec) {
	x /= vec.x;
	y /= vec.y;
	return *this;
}

inline vec2i &vec2i::operator*=(const vec2i &vec) {
	x *= vec.x;
	y *= vec.y;
	return *this;
}

inline vec2i vec2i::operator+(const vec2i &vec) const {
	return { x + vec.x, y + vec.y };
}

inline vec2i vec2i::operator-(const vec2i &vec) const {
	return { x - vec.x, y - vec.y };
}

inline vec2i vec2i::operator/(const vec2i &vec) const {
	return { x / vec.x, y / vec.y };
}

inline vec2i vec2i::operator*(const vec2i &vec) const {
	return { x * vec.x, y * vec.y };
}

inline vec2i &vec2i::operator+=(const i32 val) {
	x += val;
	y += val;
	return *this;
}

inline vec2i &vec2i::operator-=(const i32 val) {
	x -= val;
	y -= val;
	return *this;
}

inline vec2i &vec2i::operator/=(const i32 val) {
	x /= val;
	y /= val;
	return *this;
}

inline vec2i &vec2i::operator*=(const i32 val) {
	x *= val;
	y *= val;
	return *this;
}

inline vec2i vec2i::operator+(const i32 val) const {
	return { x + val, y + val };
}

inline vec2i vec2i::operator-(const i32 val) const {
	return { x - val, y - val };
}

inline vec2i vec2i::operator/(const i32 val) const {
	return { x / val, y / val };
}

inline vec2i vec2i::operator*(const i32 val) const {
	return { x * val, y * val};
}

inline bool vec2i::operator==(const vec2i &vec) const {
	return x == vec.x && y == vec.y;
}

inline bool vec2i::operator!=(const vec2i &vec) const {
	return x != vec.x && y != vec.y;
}

inline bool vec2i::operator<(const vec2i &vec) const {
	if (x != vec.x) {
		return x < vec.x;
	}
	return y < vec.y;
}

inline bool vec2i::operator<=(const vec2i &vec) const {
	if (x != vec.x) {
		return x < vec.x;
	}
	return y <= vec.y;
}

inline bool vec2i::operator>(const vec2i &vec) const {
	if (x != vec.x) {
		return x > vec.x;
	}
	return y > vec.y;
}

inline bool vec2i::operator>=(const vec2i &vec) const {
	if (x != vec.x) {
		return x > vec.x;
	}
	return y >= vec.y;
}
