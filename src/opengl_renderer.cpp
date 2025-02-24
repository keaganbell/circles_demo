#pragma once

void DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH_ARB: {
            PlatformDebugPrint("ERROR: OpenGL (0x%x): %s\n", source, message);
        } break;

        case GL_DEBUG_SEVERITY_MEDIUM_ARB: {
            PlatformDebugPrint("WARN:  OpenGL (0x%x): %s\n", source, message);
        } break;

        case GL_DEBUG_SEVERITY_LOW_ARB: {
            PlatformDebugPrint("INFO:  OpenGL (0x%x): %s\n", source, message);
        } break;
    }
}

static inline void OpenGLCreateMesh(opengl *OpenGL, mesh_index Index, mesh_object *Mesh) {
    Assert(Mesh->Vertices);
    Assert(Mesh->Indices);

    GLuint VAO;
    GLuint VBO;
    GLuint IBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    size_t VerticesSize = Mesh->VertexCount*sizeof(vertex);
    size_t IndicesSize = Mesh->IndexCount*sizeof(u16);
    glBufferData(GL_ARRAY_BUFFER, VerticesSize, Mesh->Vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndicesSize, Mesh->Indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(vertex), (void *)offsetof(vertex, Position));
    glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(vertex), (void *)offsetof(vertex, Color));

    OpenGL->Meshes[Index].VAO = VAO;
    OpenGL->Meshes[Index].VBO = VBO;
    OpenGL->Meshes[Index].IBO = IBO;
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

static GLuint CompileShader(char *VertexShaderSource, char *FragmentShaderSource) {
    GLint Success;

    GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(VertexShader, 1, &VertexShaderSource, 0);
    glCompileShader(VertexShader);
    glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &Success);
    if (Success != GL_TRUE) {
        char Buffer[1024] = {};
        glGetShaderInfoLog(VertexShader, sizeof(Buffer), 0, Buffer);
        LERROR("Vertex Shader: %s", Buffer);
    }

    GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragmentShader, 1, &FragmentShaderSource, 0);
    glCompileShader(FragmentShader);
    glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &Success);
    if (Success != GL_TRUE) {
        char Buffer[1024] = {};
        glGetShaderInfoLog(FragmentShader, sizeof(Buffer), 0, Buffer);
        LERROR("Fragment Shader: %s", Buffer);
    }

    GLuint Program = glCreateProgram();
    glAttachShader(Program, VertexShader);
    glAttachShader(Program, FragmentShader);
    glLinkProgram(Program);
    glGetProgramiv(Program, GL_LINK_STATUS, &Success);
    if (Success != GL_TRUE) {
        char Buffer[1024] = {};
        glGetProgramInfoLog(Program, sizeof(Buffer), 0, Buffer);
        LERROR("Program Link: %s", Buffer);
    }

    glValidateProgram(Program);
    glGetProgramiv(Program, GL_VALIDATE_STATUS, &Success);
    if (Success != GL_TRUE) {
        char Buffer[1024] = {};
        glGetProgramInfoLog(Program, sizeof(Buffer), 0, Buffer);
        LERROR("Program Validation: %s", Buffer);
    }

    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);

    return Program;
}

static inline void CreateUnlitProgram(opengl *OpenGL) {
    entire_file VertShaderFile = ReadEntireFile(SHADER_DIR "unlit_vert.glsl");
    entire_file FragShaderFile = ReadEntireFile(SHADER_DIR "unlit_frag.glsl");
    Assert(VertShaderFile.Contents);
    Assert(FragShaderFile.Contents);

    GLuint Handle = CompileShader(VertShaderFile.Contents, FragShaderFile.Contents);
    OpenGL->UnlitProgram.Common.Handle = Handle;
    FreeEntireFile(VertShaderFile);
    FreeEntireFile(FragShaderFile);

    glUseProgram(Handle);
    glBindAttribLocation(Handle, 0, "_Position");
    glBindAttribLocation(Handle, 1, "_Color");

    OpenGL->UnlitProgram.Transform = glGetUniformLocation(Handle, "Transform");

    glUseProgram(0);
}

static inline void CreateCircleProgram(opengl *OpenGL) {
    entire_file VertShaderFile = ReadEntireFile(SHADER_DIR "circle_vert.glsl");
    entire_file FragShaderFile = ReadEntireFile(SHADER_DIR "circle_frag.glsl");
    Assert(VertShaderFile.Contents);
    Assert(FragShaderFile.Contents);

    GLuint Handle = CompileShader(VertShaderFile.Contents, FragShaderFile.Contents);
    OpenGL->CircleProgram.Common.Handle = Handle;
    FreeEntireFile(VertShaderFile);
    FreeEntireFile(FragShaderFile);

    glUseProgram(Handle);
    glBindAttribLocation(Handle, 0, "_Position");
    glBindAttribLocation(Handle, 1, "_Color");
    glBindAttribLocation(Handle, 2, "_UV");

    OpenGL->CircleProgram.Transform = glGetUniformLocation(Handle, "Transform");
    OpenGL->CircleProgram.Radius = glGetUniformLocation(Handle, "Radius");

    glUseProgram(0);
}

static inline void CreateDebugProgram(opengl *OpenGL) {
    entire_file VertShaderFile = ReadEntireFile(SHADER_DIR "debug_vert.glsl");
    entire_file FragShaderFile = ReadEntireFile(SHADER_DIR "debug_frag.glsl");
    Assert(VertShaderFile.Contents);
    Assert(FragShaderFile.Contents);

    GLuint Handle = CompileShader(VertShaderFile.Contents, FragShaderFile.Contents);
    OpenGL->DebugProgram.Common.Handle = Handle;
    FreeEntireFile(VertShaderFile);
    FreeEntireFile(FragShaderFile);

    glUseProgram(Handle);
    glBindAttribLocation(Handle, 0, "_Position");
    glBindAttribLocation(Handle, 1, "_Color");

    OpenGL->DebugProgram.Transform = glGetUniformLocation(Handle, "Transform");

    glUseProgram(0);
}

static inline void CreateResolveProgram(opengl *OpenGL) {
    entire_file VertShaderFile = ReadEntireFile(SHADER_DIR "resolve_vert.glsl");
    entire_file FragShaderFile = ReadEntireFile(SHADER_DIR "resolve_frag.glsl");
    Assert(VertShaderFile.Contents);
    Assert(FragShaderFile.Contents);

    GLuint Handle = CompileShader(VertShaderFile.Contents, FragShaderFile.Contents);
    OpenGL->ResolveProgram.Common.Handle = Handle;
    FreeEntireFile(VertShaderFile);
    FreeEntireFile(FragShaderFile);

    glUseProgram(Handle);
    glBindAttribLocation(Handle, 0, "_Position");
    glBindAttribLocation(Handle, 1, "_UV");

    glUseProgram(0);
}

static void InitOpenGL(opengl *OpenGL) {
    glDebugMessageCallback(DebugCallback, NULL);
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    //
    // Multisample setup
    //
    glGenFramebuffers(1, &OpenGL->MultisampledFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, OpenGL->MultisampledFBO);

    glGenTextures(1, &OpenGL->MultisampledTexture);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, OpenGL->MultisampledTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 16, GL_RGBA8, TARGET_WIDTH, TARGET_HEIGHT, GL_TRUE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, OpenGL->MultisampledTexture, 0);

    glGenRenderbuffers(1, &OpenGL->DepthRBO);
    glBindRenderbuffer(GL_RENDERBUFFER, OpenGL->DepthRBO);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, 16, GL_DEPTH_COMPONENT24, TARGET_WIDTH, TARGET_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, OpenGL->DepthRBO);
    GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (Status != GL_FRAMEBUFFER_COMPLETE) {
        LERROR("Framebuffer incomplete: 0x%x", Status);
    }
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glGenFramebuffers(1, &OpenGL->ResolveFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, OpenGL->ResolveFBO);
    glGenTextures(1, &OpenGL->ResolveTexture);
    glBindTexture(GL_TEXTURE_2D, OpenGL->ResolveTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, TARGET_WIDTH, TARGET_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, OpenGL->ResolveTexture, 0);
    Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (Status != GL_FRAMEBUFFER_COMPLETE) {
        LERROR("Framebuffer incomplete: 0x%x", Status);
    }

    f32 QuadVertices[] = {
        // Positions   // TexCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
    };
    glGenVertexArrays(1, &OpenGL->ResolveVAO);
    glGenBuffers(1, &OpenGL->ResolveVBO);

    glBindVertexArray(OpenGL->ResolveVAO);
    glBindBuffer(GL_ARRAY_BUFFER, OpenGL->ResolveVBO);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBufferData(GL_ARRAY_BUFFER, sizeof(QuadVertices), QuadVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void *)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void *)(2*sizeof(float)));

    //
    // Line push buffer setup
    //
    {
        GLuint VAO;
        GLuint VBO;
        GLuint IBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &IBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glBufferData(GL_ARRAY_BUFFER, sizeof(OpenGL->LineVertexPushBufferData), 0, GL_STREAM_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(OpenGL->LineIndexPushBufferData), 0, GL_STREAM_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(line_vertex), (void *)(offsetof(line_vertex, Position)));
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(line_vertex), (void *)(offsetof(line_vertex, Color)));

        OpenGL->Meshes[MESH_INDEX_LINE_PUSH_BUFFER].VAO = VAO;
        OpenGL->Meshes[MESH_INDEX_LINE_PUSH_BUFFER].VBO = VBO;
        OpenGL->Meshes[MESH_INDEX_LINE_PUSH_BUFFER].IBO = IBO;
    }

    //
    // Quad push buffer setup
    //
    {
        GLuint VAO;
        GLuint VBO;
        GLuint IBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &IBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        glBufferData(GL_ARRAY_BUFFER, sizeof(OpenGL->QuadVertexPushBufferData), 0, GL_STREAM_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(OpenGL->QuadIndexPushBufferData), 0, GL_STREAM_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)(offsetof(vertex, Position)));
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)(offsetof(vertex, Color)));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)(offsetof(vertex, UV)));

        OpenGL->Meshes[MESH_INDEX_QUAD_PUSH_BUFFER].VAO = VAO;
        OpenGL->Meshes[MESH_INDEX_QUAD_PUSH_BUFFER].VBO = VBO;
        OpenGL->Meshes[MESH_INDEX_QUAD_PUSH_BUFFER].IBO = IBO;
    }

    //
    // Create shader programs
    //
    CreateDebugProgram(OpenGL);
    CreateUnlitProgram(OpenGL);
    CreateResolveProgram(OpenGL);
    CreateCircleProgram(OpenGL);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

static render_commands BeginFrame(opengl *OpenGL) {
    render_commands Commands = {};

    Commands.UploadQueue = OpenGL->UploadQueueData;
    Commands.MaxUploadQueueCount = ArrayCount(OpenGL->UploadQueueData);

    Commands.LineGroup.Vertices = OpenGL->LineVertexPushBufferData;
    Commands.LineGroup.MaxVertexCount = ArrayCount(OpenGL->LineVertexPushBufferData);
    Commands.LineGroup.Indices = OpenGL->LineIndexPushBufferData;
    Commands.LineGroup.MaxIndexCount = ArrayCount(OpenGL->LineIndexPushBufferData);

    Commands.QuadGroup.Vertices = OpenGL->QuadVertexPushBufferData;
    Commands.QuadGroup.MaxVertexCount = ArrayCount(OpenGL->QuadVertexPushBufferData);
    Commands.QuadGroup.Indices = OpenGL->QuadIndexPushBufferData;
    Commands.QuadGroup.MaxIndexCount = ArrayCount(OpenGL->QuadIndexPushBufferData);

    Commands.Entries = OpenGL->RenderEntryData;
    Commands.MaxRenderEntrySize = sizeof(OpenGL->RenderEntryData);

    return Commands;
}

static inline void BeginUseMesh(opengl *OpenGL, mesh_index Index) {
    glBindVertexArray(OpenGL->Meshes[Index].VAO);
    glBindBuffer(GL_ARRAY_BUFFER, OpenGL->Meshes[Index].VBO);
}

static inline void EndUseMesh() {
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

static u32 EndFrame(opengl *OpenGL, render_commands *Commands) {

    for (u32 i = 0; i < Commands->UploadQueueCount; ++i) {
        // TODO: add ability to delete meshes too
        upload_work *Work = &Commands->UploadQueue[i];
        OpenGLCreateMesh(OpenGL, Work->Index, Work->Mesh);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, OpenGL->MultisampledFBO);
    glViewport(0, 0, TARGET_WIDTH, TARGET_HEIGHT);
    glClearColor(.1f, .1f, .1f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    BeginUseMesh(OpenGL, MESH_INDEX_LINE_PUSH_BUFFER);
    glBufferSubData(GL_ARRAY_BUFFER, 0, Commands->LineGroup.VertexCount*sizeof(vertex), Commands->LineGroup.Vertices);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, Commands->LineGroup.IndexCount*sizeof(vertex), Commands->LineGroup.Indices);

    BeginUseMesh(OpenGL, MESH_INDEX_QUAD_PUSH_BUFFER);
    glBufferSubData(GL_ARRAY_BUFFER, 0, Commands->QuadGroup.VertexCount*sizeof(vertex), Commands->QuadGroup.Vertices);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, Commands->QuadGroup.IndexCount*sizeof(vertex), Commands->QuadGroup.Indices);

    //
    // Multisample pass
    //
    u32  LineGroupBaseOffset = 0;
    u32  QuadGroupBaseOffset = 0;
    u32 DrawCallCounter = 0;
    for (size_t BufferOffset = 0; BufferOffset < Commands->RenderEntrySize;) {
        render_entry_header *Typeless = Commands->Entries + BufferOffset;
        switch (Typeless->Type) {
            case TYPE_render_entry_mesh: {
                render_entry_mesh *Entry = (render_entry_mesh *)Typeless;
                BufferOffset += sizeof(*Entry);

                glUseProgram(OpenGL->UnlitProgram.Common.Handle);
                f32 Aspect = (f32)GlobalScreenWidth/GlobalScreenHeight;
                mat4 Transform = CalculateWorldTransform(Commands->Camera, Aspect);
                glUniformMatrix4fv(OpenGL->UnlitProgram.Transform, 1, GL_TRUE, Transform.Elements);

                BeginUseMesh(OpenGL, Entry->Index);

                u32 IndexCount = Commands->Assets->Meshes[Entry->Index].IndexCount;
                glDrawElements(GL_TRIANGLES, IndexCount, GL_UNSIGNED_SHORT, 0);
                ++DrawCallCounter;
            } break;

            case TYPE_render_entry_line_group: {
                render_entry_line_group *Entry = (render_entry_line_group *)Typeless;
                BufferOffset += sizeof(*Entry);

                BeginUseMesh(OpenGL, MESH_INDEX_LINE_PUSH_BUFFER);
                glUseProgram(OpenGL->DebugProgram.Common.Handle);
                f32 Aspect = (f32)GlobalScreenWidth/GlobalScreenHeight;
                mat4 Transform = CalculateWorldTransform(Commands->Camera, Aspect);
                glUniformMatrix4fv(OpenGL->DebugProgram.Transform, 1, GL_TRUE, Transform.Elements);
                glDrawElementsBaseVertex(GL_LINES, Entry->IndexCount, GL_UNSIGNED_SHORT, (GLvoid *)Entry->IndexOffset, LineGroupBaseOffset);
                ++DrawCallCounter;
                LineGroupBaseOffset += Entry->VertexCount;
            } break;

            case TYPE_render_entry_quad_group: {
                render_entry_quad_group *Entry = (render_entry_quad_group *)Typeless;
                BufferOffset += sizeof(*Entry);

                BeginUseMesh(OpenGL, MESH_INDEX_QUAD_PUSH_BUFFER);
                glUseProgram(OpenGL->CircleProgram.Common.Handle);
                f32 Aspect = (f32)GlobalScreenWidth/GlobalScreenHeight;
                mat4 Transform = CalculateWorldTransform(Commands->Camera, Aspect);
                glUniformMatrix4fv(OpenGL->CircleProgram.Transform, 1, GL_TRUE, Transform.Elements);
                glUniform1f(OpenGL->CircleProgram.Radius, 1.f);
                glDrawElementsBaseVertex(GL_TRIANGLES, Entry->IndexCount, GL_UNSIGNED_SHORT, (GLvoid *)Entry->IndexOffset, QuadGroupBaseOffset);
                ++DrawCallCounter;
                QuadGroupBaseOffset += Entry->VertexCount;
            } break;

            default:
                Assert(!"Invalid Default Case");
        }
    }

    glUseProgram(0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //
    // Resolve frame
    //
    glBindFramebuffer(GL_READ_FRAMEBUFFER, OpenGL->MultisampledFBO);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, OpenGL->ResolveFBO);
    glBlitFramebuffer(0, 0, TARGET_WIDTH, TARGET_HEIGHT,
            0, 0, TARGET_WIDTH, TARGET_HEIGHT,
            GL_COLOR_BUFFER_BIT, GL_LINEAR);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glUseProgram(OpenGL->ResolveProgram.Common.Handle);
    glBindVertexArray(OpenGL->ResolveVAO);
    glBindBuffer(GL_ARRAY_BUFFER, OpenGL->ResolveVBO);
    glViewport(0, 0, GlobalScreenWidth, GlobalScreenHeight);
    glClearColor(1.0f, 0.0f, 1.0f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindTexture(GL_TEXTURE_2D, OpenGL->ResolveTexture);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glUseProgram(0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return DrawCallCounter;
}
