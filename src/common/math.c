#include "math.h"

#include <math.h>

inline f32 lerp(f32 a, f32 b, f32 t) {
    return (1.f - t) * a + b * t;
}

inline i32 floorMod(i32 a, i32 b) {
	i32 r = a % b;
	return (r < (i32)0) ? r + b : r;
}

inline i32 floorToi32(f32 a) {
	i32 i = (i32)a;
	i -= (f32)i > a;
	return i;
}

inline f32 snap(f32 v, f32 i) {
	return floor(v / i) * i;
}

inline f32 wrap(f32 v, f32 a, f32 b) {
	if (a - b == (f32)0) {
		return b;
	}
	return v - snap(v - a, b - a);
}

inline f32 saveDivide(f32 a, f32 b) {
	return (b != (f32)0) ? a / b : (f32)0;
}

inline u32 nextPow2(u32 a) {
    --a;
    a |= a >> 1;
    a |= a >> 2;
    a |= a >> 4;
    a |= a >> 8;
    a |= a >> 16;
    return ++a;
}
