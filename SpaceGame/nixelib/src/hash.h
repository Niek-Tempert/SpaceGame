#pragma once

#include "typedefs.h"
#include "types/vec2.h"
#include "types/vec3.h"
#include "types/vec4.h"

#include <glm/common.hpp>

/* ***** Jenkins Lookup3 Hash Functions ***** */

/* Source: http://burtleburtle.net/bob/c/lookup3.c */

#define rot(x, k) (((x) << (k)) | ((x) >> (32 - (k))))

#define mix(a, b, c) \
  { \
    a -= c; \
    a ^= rot(c, 4); \
    c += b; \
    b -= a; \
    b ^= rot(a, 6); \
    a += c; \
    c -= b; \
    c ^= rot(b, 8); \
    b += a; \
    a -= c; \
    a ^= rot(c, 16); \
    c += b; \
    b -= a; \
    b ^= rot(a, 19); \
    a += c; \
    c -= b; \
    c ^= rot(b, 4); \
    b += a; \
  }

#define final(a, b, c) \
  { \
    c ^= b; \
    c -= rot(b, 14); \
    a ^= c; \
    a -= rot(c, 11); \
    b ^= a; \
    b -= rot(a, 25); \
    c ^= b; \
    c -= rot(b, 16); \
    a ^= c; \
    a -= rot(c, 4); \
    b ^= a; \
    b -= rot(a, 14); \
    c ^= b; \
    c -= rot(b, 24); \
  }

inline u32 hash_u32(u32 kx) {
	u32 a, b, c;
	a = b = c = 0xdeadbeefu + (1u << 2u) + 13u;

	a += kx;
	final(a, b, c);

	return c;
}

inline u32 hash_u322(u32 kx, u32 ky) {
	u32 a, b, c;
	a = b = c = 0xdeadbeefu + (2u << 2u) + 13u;

	b += ky;
	a += kx;
	final(a, b, c);

	return c;
}

inline u32 hash_u323(u32 kx, u32 ky, u32 kz) {
	u32 a, b, c;
	a = b = c = 0xdeadbeefu + (3u << 2u) + 13u;

	c += kz;
	b += ky;
	a += kx;
	final(a, b, c);

	return c;
}

inline u32 hash_u324(u32 kx, u32 ky, u32 kz, u32 kw) {
	u32 a, b, c;
	a = b = c = 0xdeadbeefu + (4u << 2u) + 13u;

	a += kx;
	b += ky;
	c += kz;
	mix(a, b, c);

	a += kw;
	final(a, b, c);

	return c;
}

#undef rot
#undef final
#undef mix

inline u32 hash_int(int kx) {
	return hash_u32(u32(kx));
}

inline u32 hash_int2(int kx, int ky) {
	return hash_u322(u32(kx), u32(ky));
}

inline u32 hash_int3(int kx, int ky, int kz) {
	return hash_u323(u32(kx), u32(ky), u32(kz));
}

inline u32 hash_int4(int kx, int ky, int kz, int kw) {
	return hash_u324(u32(kx), u32(ky), u32(kz), u32(kw));
}

/* Hashing u32 or u32[234] into a float in the range [0, 1]. */

inline float hash_u32_to_float(u32 kx) {
	return float(hash_u32(kx)) / float(0xFFFFFFFFu);
}

inline float hash_u322_to_float(u32 kx, u32 ky) {
	return float(hash_u322(kx, ky)) / float(0xFFFFFFFFu);
}

inline auto hash_u323_to_float(u32 kx, u32 ky, u32 kz) -> float {
	return float(hash_u323(kx, ky, kz)) / float(0xFFFFFFFFu);
}

inline float hash_u324_to_float(u32 kx, u32 ky, u32 kz, u32 kw) {
	return float(hash_u324(kx, ky, kz, kw)) / float(0xFFFFFFFFu);
}

/* Hashing float or vec[234] into a float in the range [0, 1]. */

inline float hash_float_to_float(float k) {
	return hash_u32_to_float(*reinterpret_cast<u32 *>(&k));
}

inline float hash_vec2f_to_float(vec2f k) {
	return hash_u322_to_float(*reinterpret_cast<u32 *>(&k.x), *reinterpret_cast<u32 *>(&k.y));
}

inline float hash_vec3f_to_float(vec3f k) {
	return hash_u323_to_float(*reinterpret_cast<u32 *>(&k.x), *reinterpret_cast<u32 *>(&k.y), *reinterpret_cast<u32 *>(&k.z));
}

inline float hash_vec4f_to_float(vec4f k) {
	return hash_u324_to_float(
			*reinterpret_cast<u32 *>(&k.x), *reinterpret_cast<u32 *>(&k.y), *reinterpret_cast<u32 *>(&k.z), *reinterpret_cast<u32 *>(&k.w));
}

/* Hashing vec[234] into vec[234] of components in the range [0, 1]. */

inline vec2f hash_vec2f_to_vec2f(vec2f k) {
	return vec2f(hash_vec2f_to_float(k), hash_vec3f_to_float(vec3f(k.x, k.y, 1.0)));
}

inline vec3f hash_vec3f_to_vec3f(vec3f k) {
	return vec3f(hash_vec3f_to_float(k), hash_vec4f_to_float(vec4f(k.x, k.y, k.z, 1.0)), hash_vec4f_to_float(vec4f(k.x, k.x, k.z, 2.0)));
}

inline vec4f hash_vec4f_to_vec4f(vec4f k) {
	return vec4f(hash_vec4f_to_float({ k.x, k.y, k.z, k.w }),
			hash_vec4f_to_float({ k.w, k.x, k.y, k.z }),
			hash_vec4f_to_float({ k.z, k.w, k.x, k.y }),
			hash_vec4f_to_float({ k.y, k.z, k.w, k.x }));
}

/* Hashing float or vec[234] into vec3f of components in range [0, 1]. */

inline vec3f hash_float_to_vec3f(float k) {
	return vec3f(hash_float_to_float(k), hash_vec2f_to_float(vec2f(k, 1.0)), hash_vec2f_to_float(vec2f(k, 2.0)));
}

inline vec3f hash_vec2f_to_vec3f(vec2f k) {
	return vec3f(hash_vec2f_to_float(k), hash_vec3f_to_float(vec3f(k.x, k.y, 1.0)), hash_vec3f_to_float(vec3f(k.x, k.y, 2.0)));
}

inline vec3f hash_vec4f_to_vec3f(vec4f k) {
	return vec3f(hash_vec4f_to_float({ k.x, k.y, k.z, k.w }), hash_vec4f_to_float({ k.z, k.x, k.w, k.y }), hash_vec4f_to_float({ k.w, k.z, k.y, k.x }));
}

/* Hashing float or vec[234] into vec2f of components in range [0, 1]. */

inline vec2f hash_float_to_vec2f(float k) {
	return vec2f(hash_float_to_float(k), hash_vec2f_to_float(vec2f(k, 1.0)));
}

inline vec2f hash_vec3f_to_vec2f(vec3f k) {
	return vec2f(hash_vec3f_to_float({ k.x, k.y, k.z }), hash_vec3f_to_float({ k.z, k.x, k.y }));
}

inline vec2f hash_vec4f_to_vec2f(vec4f k) {
	return vec2f(hash_vec4f_to_float({ k.x, k.y, k.z, k.w }), hash_vec4f_to_float({ k.z, k.x, k.w, k.y }));
}

/* Other Hash Functions */

inline float integer_noise(int n) {
	/* Integer bit-shifts for these calculations can cause precision problems on macOS.
	 * Using u32 resolves these issues. */
	u32 nn;
	nn = (u32(n) + 1013u) & 0x7fffffffu;
	nn = (nn >> 13u) ^ nn;
	nn = (u32(nn * (nn * nn * 60493u + 19990303u)) + 1376312589u) & 0x7fffffffu;
	return 0.5f * (float(nn) / 1073741824.0f);
}

inline float wang_hash_noise(u32 s) {
	s = (s ^ 61u) ^ (s >> 16u);
	s *= 9u;
	s = s ^ (s >> 4u);
	s *= 0x27d4eb2du;
	s = s ^ (s >> 15u);

	return glm::fract(float(s) / 4294967296.0);
}