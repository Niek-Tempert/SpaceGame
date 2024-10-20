#pragma once

#include <cmath>

#include "macros.h"
#include "types.h"

#define DEFINE_INT_MATH(int_t) \
static inline NODISCARD bool is_even(int_t a) { \
	return (a % 2) == 0; \
} \
static inline NODISCARD bool is_odd(int_t a) { \
	return (a % 2) != 0; \
} \
/* Return 0 if the divisor is 0 */ \
static inline NODISCARD int_t save_divide(int_t a, int_t b) { \
	return (b != 0) ? a / b : 0; \
} \
/* Floored modulo: Continuous positive */ \
static inline NODISCARD int_t floor_mod(int_t a, int_t b) { \
	int_t r = a % b; \
	return (r < 0) ? r + b : r; \
}

#define DEFINE_FLOAT_INT_MATH(float_t, int_t) \
static inline NODISCARD int_t floor_to_##int_t(float_t a) { \
	int_t i = (int_t)a; \
	i -= (float_t)i > a; \
	return i; \
}

#define DEFINE_FLOAT_MATH(float_t) \
/* TODO: Take a look at https://en.cppreference.com/w/c/numeric/math/floor */ \
static inline NODISCARD float_t floor_mod(float_t a, float_t b) { \
	const float_t r = fmod(a, b); \
	return (r < 0) ? r + b : r; \
}

#define DEFINE_NUMBER_MATH(number_t) \
/* TODO: See if native min/max functions are faster */ \
static inline NODISCARD number_t min(number_t a, number_t b) { \
	return a < b ? a : b; \
} \
static inline NODISCARD number_t max(number_t a, number_t b) { \
	return a > b ? a : b; \
} \
static inline NODISCARD number_t clamp(number_t x, number_t a, number_t b) { \
	return max(a, max(b, x)); \
}

DEFINE_INT_MATH(i8);
DEFINE_INT_MATH(i16);
DEFINE_INT_MATH(i32);
DEFINE_INT_MATH(i64);
DEFINE_INT_MATH(u8);
DEFINE_INT_MATH(u16);
DEFINE_INT_MATH(u32);
DEFINE_INT_MATH(u64);

DEFINE_FLOAT_MATH(f32);
DEFINE_FLOAT_MATH(f64);

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

#undef DEFINE_INT_MATH
#undef DEFINE_FLOAT_MATH
#undef DEFINE_FLOAT_INT_MATH
#undef DEFINE_NUMBER_MATH