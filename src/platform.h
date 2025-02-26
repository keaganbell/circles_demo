#pragma once
#include "stdlib.h"

static void *PlatformAllocate(size_t Size);
static void PlatformDebugPrint(const char *Message, ...);
static void PlatformMessageBox(const char *Message, ...);

struct entire_file {
    char *Contents;
    size_t Size;
};

static inline entire_file ReadEntireFile(char *Filename) {
    entire_file Result = {};
    FILE *File = fopen(Filename, "rb");
    if (File) {
        fseek(File, 0, SEEK_END);
        Result.Size = ftell(File);
        rewind(File);
        LINFO("Loading file %s with size %zu bytes.", Filename, Result.Size);
        Result.Contents = (char *)malloc(Result.Size + 1);
        fread(Result.Contents, 1, Result.Size, File);
        Result.Contents[Result.Size] = '\0';
    }
    else {
        LERROR("Failed to load file %s.", Filename);
    }
    return Result;
}

static inline void FreeEntireFile(entire_file File) {
    Assert(File.Contents);
    free(File.Contents);
}
