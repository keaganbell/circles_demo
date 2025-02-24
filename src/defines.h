#pragma once
#include "stddef.h"
#include "stdint.h"

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t b8;
typedef int32_t b32;
//#define true 1
//#define false 0

typedef float  f32;
typedef double f64;

#define UNUSED(x) (void)x
#define ArrayCount(Array) (sizeof(Array)/sizeof(Array[0]))

#define GiB (1<<30)
#define MiB (1<<20)
#define kiB (1<<10)
