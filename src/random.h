#pragma once

struct random_series {
    u32 Seed;
};

static inline random_series InitRandom(u32 Seed) {
    random_series Result = {};
    Result.Seed = Seed;
    return Result;
}

#define MAX_RANDOM_UINT 2147483647
static inline u32 RandomUint32(random_series *Series) {
    // Apparently u32 automatically wraps in C
    Series->Seed = (1664525 * Series->Seed + 1013904223) % MAX_RANDOM_UINT;
    return Series->Seed;
}

static inline u32 RandomChoice(random_series *Series, u32 Count) {
    return RandomUint32(Series) % Count;
}

static inline f32 RandomFloat(random_series *Series) {
    f32 Divisor = 1.f/(f32)MAX_RANDOM_UINT;
    return Divisor*(f32)RandomUint32(Series);
}

static inline f32 RandomBilateral(random_series *Series) {
    return 2.f*RandomFloat(Series) - 1.f;
}

static inline i32 RandomRange(random_series *Series, i32 Min, i32 Max) {
    i32 Range = Max - Min;
    return Min + (i32)RandomChoice(Series, Range);
}

static inline f32 RandomRange(random_series *Series, f32 Min, f32 Max) {
    i32 Range = Max - Min;
    return Min + Range*RandomFloat(Series);
}
