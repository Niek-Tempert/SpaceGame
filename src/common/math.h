#ifndef BASE_MATH_H
#define BASE_MATH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "types.h"

#define CLAMP(value, min, max) ((value) < (min) ? (min) : ((value) > (max) ? (max) : (value)))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

f32 lerp(f32 a, f32 b, f32 t);
i32 floorMod(i32 a, i32 b);
i32 floorToi32(f32 a);
f32 snap(f32 v, f32 i);
f32 wrap(f32 v, f32 a, f32 b);
f32 saveDivide(f32 a, f32 b);
u32 nextPow2(u32 a);

#ifdef __cplusplus
}
#endif

#endif
