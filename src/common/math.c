#include "math.h"

#include <math.h>

f32 lerp(f32 a, f32 b, f32 t) {
    return (1.f - t) * a + b * t;
}

i32 floor_mod(i32 a, i32 b) {
	i32 r = a % b;
	return (r < (i32)0) ? r + b : r;
}

i32 floor_to_i32(f32 a) {
	i32 i = (i32)a;
	i -= (f32)i > a;
	return i;
}

f32 snap(f32 v, f32 i) {
	return floor(v / i) * i;
}

f32 wrap(f32 v, f32 a, f32 b) {
	if (a - b == (f32)0) {
		return b;
	}
	return v - snap(v - a, b - a);
}

f32 save_divide(f32 a, f32 b) {
	return (b != (f32)0) ? a / b : (f32)0;
}