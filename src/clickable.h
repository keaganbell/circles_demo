#pragma once

struct program_memory {
    b32 Initialized;
    void *PersistantMemory;
    size_t PersistantMemorySize;
};

struct camera {
    vec3 Position;
    vec3 Target;
    vec3 Up;
    f32 FOV;
    f32 Near;
    f32 Far;
};

struct vertex {
    vec4 Color;
    vec3 Position;
    vec2 UV;
};

struct line_vertex {
    vec4 Color;
    vec3 Position;
};

struct mesh_object {
    vertex *Vertices;
    u32 VertexCount;

    u16 *Indices;
    u32 IndexCount;
};

enum mesh_index {
    MESH_INDEX_LINE_PUSH_BUFFER,
    MESH_INDEX_QUAD_PUSH_BUFFER,
    MESH_INDEX_TEST_OBJECT,

    MESH_INDEX_MAX_COUNT
};

struct assets {
    memory_arena VertexArena;
    memory_arena IndexArena;

    // every mesh_object in the asset
    // store needs an entry in mesh_index
    mesh_object Meshes[MESH_INDEX_MAX_COUNT];
};

struct upload_work {
    // TODO: figure out a good way of identifying the mesh
    // options: Index into array, GUID into a hash table, ??
    mesh_index Index;
    mesh_object *Mesh;
};

enum render_entry_type {
    TYPE_render_entry_line_group,
    TYPE_render_entry_quad_group,
    TYPE_render_entry_mesh,
};

struct render_entry_header {
    render_entry_type Type;
};

struct render_entry_mesh {
    render_entry_header Header;
    mesh_index Index;
};

struct render_entry_line_group {
    render_entry_header Header;

    line_vertex *Vertices;
    u32 VertexCount;

    u16 *Indices;
    u32 IndexCount;
    size_t IndexOffset;
};

struct render_entry_quad_group {
    render_entry_header Header;

    vertex *Vertices;
    u32 VertexCount;

    u16 *Indices;
    u32 IndexCount;
    size_t IndexOffset;
};

struct vertex_group {
    vertex *Vertices;
    u32 VertexCount;
    u32 MaxVertexCount;

    u16 *Indices;
    u32 IndexCount;
    u32 MaxIndexCount;
};

struct line_vertex_group {
    line_vertex *Vertices;
    u32 VertexCount;
    u32 MaxVertexCount;

    u16 *Indices;
    u32 IndexCount;
    u32 MaxIndexCount;
};

struct render_commands {
    line_vertex_group LineGroup;
    vertex_group QuadGroup;

    upload_work *UploadQueue;
    u32 UploadQueueCount;
    u32 MaxUploadQueueCount;

    render_entry_header *Entries;
    size_t RenderEntrySize;
    size_t MaxRenderEntrySize;

    render_entry_line_group *CurrentLines;
    render_entry_quad_group *CurrentQuads;

    assets *Assets;
    camera *Camera;
    vec3 WorldUp;

    u32 CircleCount;
};

struct bounding_box {
    vec3 Position;
    vec3 Bounds;
};

#if 0
struct planar_collider {
    vec3 Position;
    vec3 Normal;
    vec3 *Points;
    u32 PointCount;

    // TODO: figure out the data structure
    planar_collider *Next;
};
#endif

struct circle_object {
    vec4 Color;
    vec3 Position;
    vec3 Velocity;
    f32 Radius;

    circle_object *Next;
    circle_object *Prev;
};

#define MAX_CIRCLE_COUNT (1<<16)
struct program_state {
    memory_arena PermanentArena;

    bounding_box TestBox;

    circle_object Circles[MAX_CIRCLE_COUNT];
    u32 CircleCount;
    circle_object *FirstActiveCircle;
    circle_object *FirstFreeCircle;
    circle_object *HotCircle;

    assets Assets;
    camera Camera;
};
