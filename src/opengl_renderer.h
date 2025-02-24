#pragma once

struct opengl_shader_common {
    GLuint Handle;
};

struct opengl_simple_unlit_program {
    opengl_shader_common Common;
    GLuint Transform;
};

struct opengl_resolve_frame_program {
    opengl_shader_common Common;
};

struct opengl_debug_program {
    opengl_shader_common Common;
    GLuint Transform;
};

struct opengl_unlit_circle_program {
    opengl_shader_common Common;
    GLuint Transform;
    GLuint Radius;
};

struct opengl_mesh {
    GLuint VAO;
    GLuint VBO;
    GLuint IBO;
};

#define TARGET_WIDTH 1920
#define TARGET_HEIGHT 1080
#define MAX_UPLOAD_QUEUE_COUNT (1<<8)
#define MAX_RENDER_ENTRY_COUNT (1<<10)
#define MAX_VERTEX_COUNT (1<<20)
#define MAX_INDEX_COUNT (1<<24)
struct opengl {
    upload_work UploadQueueData[MAX_UPLOAD_QUEUE_COUNT];
    render_entry_header RenderEntryData[MAX_RENDER_ENTRY_COUNT];
    line_vertex LineVertexPushBufferData[MAX_VERTEX_COUNT];
    u16 LineIndexPushBufferData[MAX_INDEX_COUNT];
    vertex QuadVertexPushBufferData[MAX_VERTEX_COUNT];
    u16 QuadIndexPushBufferData[MAX_INDEX_COUNT];

    opengl_mesh Meshes[MESH_INDEX_MAX_COUNT];

    GLuint MultisampledTexture;
    GLuint MultisampledFBO;
    GLuint DepthRBO;

    GLuint ResolveTexture;
    GLuint ResolveFBO;
    GLuint ResolveVAO;
    GLuint ResolveVBO;

    opengl_debug_program DebugProgram;
    opengl_simple_unlit_program UnlitProgram;
    opengl_unlit_circle_program CircleProgram;
    opengl_resolve_frame_program ResolveProgram;
};
