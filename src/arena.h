#pragma once

struct memory_arena {
    u8 *Base;
    size_t Used;
    size_t Cap;
};

static inline memory_arena CreateArena(void *Base, size_t Cap) {
    memory_arena Result = {};
    Result.Base = (u8 *)Base;
    Result.Cap = Cap;
    return Result;
}

#define PushSize(Arena, Size) _PushArena(Arena, Size)
#define PushArray(Arena, Type, Count) (Type *)_PushArena(Arena, sizeof(Type)*Count)
#define PushStruct(Arena, Type) (Type *)_PushArena(Arena, sizeof(Type))
static inline void *_PushArena(memory_arena *Arena, size_t Size) {
    void *Result = NULL;
    Assert(Arena->Used < SIZE_MAX - Size);
    if (Arena->Used + Size < Arena->Cap) {
        Result = Arena->Base + Arena->Used;
        Arena->Used += Size;
    }
    return Result;
}

static inline size_t GetRemainingSize(memory_arena *Arena) {
    return Arena->Cap - Arena->Used;
}

// TODO: temporary arenas
