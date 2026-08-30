#pragma once

#include <cmath>

#include "macros.h"
#include "common/types.h"

namespace nixemath {

#define DEFINE_INT_MATH(int_t) \
static constexpr FORCEINLINE PURE bool is_even(const int_t a) { \
	return (a % (int_t)2) == (int_t)0; \
} \
static constexpr FORCEINLINE PURE bool is_odd(const int_t a) { \
	return (a % (int_t)2) != (int_t)0; \
} \
/* Floored modulo: Continuous positive */ \
static FORCEINLINE PURE int_t floor_mod(const int_t a, const int_t b) { \
	const int_t r = a % b; \
	return (r < (int_t)0) ? r + b : r; \
}

#define DEFINE_FLOAT_INT_MATH(float_t, int_t) \
static constexpr FORCEINLINE PURE int_t floor_to_##int_t(const float_t a) { \
	int_t i = (int_t)a; \
	i -= (float_t)i > a; \
	return i; \
}

#define DEFINE_FLOAT_MATH(float_t) \
/* TODO: Take a look at https://en.cppreference.com/w/c/numeric/math/floor */ \
static FORCEINLINE PURE float_t floor_mod(const float_t a, const float_t b) { \
	const float_t r = fmod(a, b); \
	return (r < (float_t)0) ? r + b : r; \
} \
static constexpr FORCEINLINE PURE float_t invlerp(const float_t a, const float_t b, const float_t v) { \
	return (v - a) / (b - a); \
} \
static constexpr FORCEINLINE PURE float_t remap(const float_t v, const float_t imin, const float_t imax, const float_t omin, const float_t omax) { \
	return omin + (v - imin) * (omax - omin) / (imax - imin); \
} \
static FORCEINLINE PURE float_t snap(const float_t v, const float_t i) { \
	return floor(v / i) * i; \
} \
static constexpr FORCEINLINE PURE float_t wrap(const float_t v, const float_t a, const float_t b) { \
	if (a - b == (float_t)0) { \
		return b; \
	} \
	return v - snap(v - a, b - a); \
} \
/* https://iquilezles.org/www/articles/smin/smin.htm */ \
static constexpr FORCEINLINE PURE float_t smin(const float_t v, const float_t l, const float_t s) { \
	if (s == (float_t)0) { \
		return min(v, l); \
	} \
	const float_t h = max(s - abs(v - l), (float_t)0) / s; \
	return min(v, l) - h * h * h * s * (float_t)(1.0 / 6.0); \
} \
static constexpr FORCEINLINE PURE float_t smax(float_t v, float_t l, float_t s) { \
	return -smin(-v, -l, s); \
}

#define DEFINE_NUMBER_MATH(number_t) \
/* TODO: See if native min/max functions are faster */ \
static constexpr FORCEINLINE PURE number_t min(const number_t a, const number_t b) { \
	return a < b ? a : b; \
} \
static constexpr FORCEINLINE PURE number_t max(const number_t a, const number_t b) { \
	return a > b ? a : b; \
} \
static constexpr FORCEINLINE PURE number_t clamp(const number_t x, const number_t a, const number_t b) { \
	return max(a, min(b, x)); \
} \
/* Return 0 if the divisor is 0 */ \
static constexpr FORCEINLINE PURE number_t save_divide(const number_t a, const number_t b) { \
	return (b != (number_t)0) ? a / b : (number_t)0; \
}

#define DEFINE_SIGNED_MATH(signed_t) \
static constexpr FORCEINLINE PURE signed_t abs(const signed_t a) { \
	return max((signed_t)-a, a); \
}

#define DEFINE_UNSIGNED_MATH(unsigned_t) \
static constexpr FORCEINLINE PURE unsigned_t abs(const unsigned_t a) { \
	return a; \
}

DEFINE_INT_MATH(i8);
DEFINE_INT_MATH(i16);
DEFINE_INT_MATH(i32);
DEFINE_INT_MATH(i64);
DEFINE_INT_MATH(u8);
DEFINE_INT_MATH(u16);
DEFINE_INT_MATH(u32);
DEFINE_INT_MATH(u64);

DEFINE_FLOAT_INT_MATH(f32, i8);
DEFINE_FLOAT_INT_MATH(f32, i16);
DEFINE_FLOAT_INT_MATH(f32, i32);
DEFINE_FLOAT_INT_MATH(f32, i64);
DEFINE_FLOAT_INT_MATH(f64, i8);
DEFINE_FLOAT_INT_MATH(f64, i16);
DEFINE_FLOAT_INT_MATH(f64, i32);
DEFINE_FLOAT_INT_MATH(f64, i64);
DEFINE_FLOAT_INT_MATH(f32, u8);
DEFINE_FLOAT_INT_MATH(f32, u16);
DEFINE_FLOAT_INT_MATH(f32, u32);
DEFINE_FLOAT_INT_MATH(f32, u64);
DEFINE_FLOAT_INT_MATH(f64, u8);
DEFINE_FLOAT_INT_MATH(f64, u16);
DEFINE_FLOAT_INT_MATH(f64, u32);
DEFINE_FLOAT_INT_MATH(f64, u64);

DEFINE_NUMBER_MATH(i8);
DEFINE_NUMBER_MATH(i16);
DEFINE_NUMBER_MATH(i32);
DEFINE_NUMBER_MATH(i64);
DEFINE_NUMBER_MATH(u8);
DEFINE_NUMBER_MATH(u16);
DEFINE_NUMBER_MATH(u32);
DEFINE_NUMBER_MATH(u64);
DEFINE_NUMBER_MATH(f32);
DEFINE_NUMBER_MATH(f64);

DEFINE_SIGNED_MATH(i8);
DEFINE_SIGNED_MATH(i16);
DEFINE_SIGNED_MATH(i32);
DEFINE_SIGNED_MATH(i64);
DEFINE_SIGNED_MATH(f32);
DEFINE_SIGNED_MATH(f64);

DEFINE_UNSIGNED_MATH(u8);
DEFINE_UNSIGNED_MATH(u16);
DEFINE_UNSIGNED_MATH(u32);
DEFINE_UNSIGNED_MATH(u64);

DEFINE_FLOAT_MATH(f32);
DEFINE_FLOAT_MATH(f64);

#undef DEFINE_INT_MATH
#undef DEFINE_FLOAT_MATH
#undef DEFINE_FLOAT_INT_MATH
#undef DEFINE_NUMBER_MATH

}
