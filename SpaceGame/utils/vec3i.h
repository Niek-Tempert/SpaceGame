#pragma once

#include "../nixelib/nixelib.h"

struct vec3i
{
    i32 x;
    i32 y;
    i32 z;

    vec3i() : x(0), y(0), z(0) {}
    vec3i(i32 x, i32 y, i32 z) : x(x), y(y), z(z) {}

    vec3i &operator+=(const vec3i &vec);
    vec3i operator+(const vec3i &vec) const;
    vec3i &operator-=(const vec3i &vec);
    vec3i operator-(const vec3i &vec) const;
    vec3i &operator/=(const vec3i &vec);
    vec3i operator/(const vec3i &vec) const;
    vec3i &operator*=(const vec3i &vec);
    vec3i operator*(const vec3i &vec) const;

    vec3i &operator+=(i32 val);
    vec3i operator+(i32 val) const;
    vec3i &operator-=(i32 val);
    vec3i operator-(i32 val) const;
    vec3i &operator/=(i32 val);
    vec3i operator/(i32 val) const;
    vec3i &operator*=(i32 val);
    vec3i operator*(i32 val) const;

    bool operator==(const vec3i &vec) const;
    bool operator!=(const vec3i &vec) const;
    bool operator<(const vec3i &vec) const;
    bool operator<=(const vec3i &vec) const;
    bool operator>(const vec3i &vec) const;
    bool operator>=(const vec3i &vec) const;
};

inline vec3i& vec3i::operator+=(const vec3i& vec)
{
    x += vec.x;
    y += vec.y;
    z += vec.z;
    return *this;
}

inline vec3i& vec3i::operator-=(const vec3i& vec)
{
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;
    return *this;
}

inline vec3i& vec3i::operator/=(const vec3i& vec)
{
    x /= vec.x;
    y /= vec.y;
    z /= vec.z;
    return *this;
}

inline vec3i& vec3i::operator*=(const vec3i& vec)
{
    x *= vec.x;
    y *= vec.y;
    z *= vec.z;
    return *this;
}

inline vec3i vec3i::operator+(const vec3i& vec) const
{
    return {x + vec.x, y + vec.y, z + vec.z};
}

inline vec3i vec3i::operator-(const vec3i& vec) const
{
    return {x - vec.x, y - vec.y, z - vec.z};
}

inline vec3i vec3i::operator/(const vec3i& vec) const
{
    return {x / vec.x, y / vec.y, z / vec.z};
}

inline vec3i vec3i::operator*(const vec3i& vec) const
{
    return {x * vec.x, y * vec.y, z * vec.z};
}

inline vec3i& vec3i::operator+=(const i32 val)
{
    x += val;
    y += val;
    z += val;
    return *this;
}

inline vec3i& vec3i::operator-=(const i32 val)
{
    x -= val;
    y -= val;
    z -= val;
    return *this;
}

inline vec3i& vec3i::operator/=(const i32 val)
{
    x /= val;
    y /= val;
    z /= val;
    return *this;
}

inline vec3i& vec3i::operator*=(const i32 val)
{
    x *= val;
    y *= val;
    z *= val;
    return *this;
}

inline vec3i vec3i::operator+(const i32 val) const
{
    return {x + val, y + val, z + val};
}

inline vec3i vec3i::operator-(const i32 val) const
{
    return {x - val, y - val, z - val};
}

inline vec3i vec3i::operator/(const i32 val) const
{
    return {x / val, y / val, z / val};
}

inline vec3i vec3i::operator*(const i32 val) const
{
    return {x * val, y * val, z * val};
}

inline bool vec3i::operator==(const vec3i& vec) const
{
    return x == vec.x && y == vec.y && z == vec.z;
}

inline bool vec3i::operator!=(const vec3i& vec) const
{
    return x != vec.x && y != vec.y && z != vec.z;
}

inline bool vec3i::operator<(const vec3i& vec) const
{
    if (x != vec.x) {
        return x < vec.x;
    }
    if (y != vec.y) {
        return y < vec.y;
    }
    return z < vec.z;
}

inline bool vec3i::operator<=(const vec3i& vec) const
{
    if (x != vec.x) {
        return x < vec.x;
    }
    if (y != vec.y) {
        return y < vec.y;
    }
    return z <= vec.z;
}

inline bool vec3i::operator>(const vec3i& vec) const
{
    if (x != vec.x) {
        return x > vec.x;
    }
    if (y != vec.y) {
        return y > vec.y;
    }
    return z > vec.z;
}

inline bool vec3i::operator>=(const vec3i& vec) const
{
    if (x != vec.x) {
        return x > vec.x;
    }
    if (y != vec.y) {
        return y > vec.y;
    }
    return z >= vec.z;
}
