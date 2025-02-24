#pragma once
#define COLOR_RED   vec4(1.f, 0.f, 0.f, 1.f)
#define COLOR_GREEN vec4(0.f, 1.f, 0.f, 1.f)
#define COLOR_BLUE  vec4(0.f, 0.f, 1.f, 1.f)

static random_series GlobalRandom;

static inline void RotateCamera(camera *Camera, f32 Amount, vec3 V) {
    quaternion Q = quaternion(Amount, V);
    Camera->Target = Normalized(Rotate(Camera->Target, Q));
    Camera->Up = Normalized(Rotate(Camera->Up, Q));
}

static inline mat4 CalculateCameraView(camera *Camera) {
    vec3 P = Camera->Position;
    vec3 T = Camera->Target;
    vec3 U = Camera->Up;
    vec3 R = Cross(T, U);

    f32 x = R.x*P.x + U.x*P.y + T.x*P.z;
    f32 y = R.y*P.x + U.y*P.y + T.y*P.z;
    f32 z = R.z*P.x + U.z*P.y + T.z*P.z;
    mat4 View = {
        R.x, U.x, T.x, -x,
        R.y, U.y, T.y, -y,
        R.z, U.z, T.z, -z,
        0.f, 0.f, 0.f, 1.f
    };
    return View;
}

static inline mat4 CalculateInverseCameraView(camera *Camera) {
    vec3 P = Camera->Position;
    vec3 T = Camera->Target;
    vec3 U = Camera->Up;
    vec3 R = Cross(T, U);

    mat4 InverseView = {
        R.x, R.y, R.z, P.x, 
        U.x, U.y, U.z, P.y,
        T.x, T.y, T.z, P.z,
        0.f, 0.f, 0.f, 1.f
    };
    return InverseView;
}

static inline mat4 CalculateWorldTransform(camera *Camera, f32 Aspect) {
    f32 h = Camera->Near*tanf(Camera->FOV/2.f);
    f32 w = Aspect*h;

    f32 a = -1.f/w;
    f32 b = -1.f/h;
    f32 c = 2.f/(Camera->Near - Camera->Far);
    f32 d = (Camera->Near + Camera->Far)/(Camera->Near - Camera->Far);
    f32 e = 1.f;
    mat4 Projection = {
          a, 0.f, 0.f, 0.f,
        0.f,   b, 0.f, 0.f,
        0.f, 0.f,   c,   d,
        0.f, 0.f,   e, 0.f,
    };
    return Projection*CalculateCameraView(Camera);
}

static inline mat4 CalculateInverseWorldTransform(camera *Camera, f32 Aspect) {
    f32 h = Camera->Near*tanf(Camera->FOV/2.f);
    f32 w = Aspect*h;

    f32 a = -1.f/w;
    f32 b = -1.f/h;
    f32 c = 2.f/(Camera->Near - Camera->Far);
    f32 d = (Camera->Near + Camera->Far)/(Camera->Near - Camera->Far);
    f32 e = 1.f;
    mat4 InverseProjection = {
        1.f/a,   0.f,   0.f,   0.f,
          0.f, 1.f/b,   0.f,   0.f,
          0.f,   0.f,   0.f, 1.f/e,
          0.f,   0.f, 1.f/d, -c/(d*e)
    };
    return CalculateInverseCameraView(Camera)*InverseProjection;
}

static void InitCamera(camera *Camera) {
        Camera->FOV = PI/2.f;
        Camera->Near = -0.5f;
        Camera->Far = -100.f;
        Camera->Up = vec3(0.f, 1.f, 0.f);
        Camera->Target = vec3(0.f, 0.f, -1.f);
#if 0
        Camera->Position = vec3(0.f, -8.f, 10.f);
        RotateCamera(Camera, 0.5f, vec3(1.f, 0.f, 0.f));
#else
        Camera->Position = vec3(0.f, 0.f, 10.f);
        RotateCamera(Camera, 0.f, vec3(1.f, 0.f, 0.f));
#endif
}

static void CreatePlane(assets  *Assets, mesh_object *Mesh, vec3 CenterP, f32 Width, f32 Height, u32 VertexCount, vec4 Color = vec4(1.0f)) {
    u32 QuadCount = (VertexCount - 1)*(VertexCount - 1);
    u32 IndexCount = 6*QuadCount;
    u32 TotalVertexCount = VertexCount*VertexCount;
    vertex *Vertices = PushArray(&Assets->VertexArena, vertex, TotalVertexCount);
    u16 *Indices = PushArray(&Assets->IndexArena, u16, IndexCount);

    if (Vertices && Indices) {
        Mesh->VertexCount = TotalVertexCount;
        Mesh->IndexCount = IndexCount;
        Mesh->Vertices = Vertices;
        Mesh->Indices = Indices;

        f32 SpacingX = (f32)Width/VertexCount;
        f32 SpacingY = (f32)Height/VertexCount;
        for (u32 j = 0; j < VertexCount; ++j) {
            for (u32 i = 0; i < VertexCount; ++i) {
                u32 Index = j*VertexCount + i;
                Vertices[Index].Position = CenterP + vec3(vec2((f32)i*SpacingX, (f32)j*SpacingY), 0.f) - vec3(0.5f*vec2(Width - SpacingX, Height - SpacingY), 0.f);
                Vertices[Index].Position.z += 0.15f*RandomBilateral(&GlobalRandom);
                Vertices[Index].Color = Color;
            }
        }

        u32 QuadCounter = 0;
        for (u32 i = 0; i < TotalVertexCount - (VertexCount - 1); ++i) {
            if (i % VertexCount < (VertexCount - 1)) {
                Assert(QuadCounter <= QuadCount);
                Indices[QuadCounter*6 + 0] = i + 0;
                Indices[QuadCounter*6 + 1] = i + 1;
                Indices[QuadCounter*6 + 2] = i + 1 + VertexCount;
                Indices[QuadCounter*6 + 3] = i + 1 + VertexCount;
                Indices[QuadCounter*6 + 4] = i + VertexCount;
                Indices[QuadCounter*6 + 5] = i + 0;
                ++QuadCounter;
            }
        }
    }
    else {
        u32 RemainingVertexCount = GetRemainingSize(&Assets->VertexArena)/sizeof(vertex);
        u32 RemainingIndexCount = GetRemainingSize(&Assets->IndexArena)/sizeof(u16);
        LWARN("Failed to create plane. Required %zu vertices and %zu indices, but there was only space for %zu and %zu", TotalVertexCount, IndexCount, RemainingVertexCount, RemainingIndexCount);
    }
}

static inline void InitAssetStore(assets *Assets, memory_arena *Arena) {
    size_t VertexStoreSize = 12*MiB;
    void *VertexBase = PushSize(Arena, VertexStoreSize);
    Assert(VertexBase);
    Assets->VertexArena = CreateArena(VertexBase, VertexStoreSize);

    size_t IndexStoreSize = 12*MiB;
    void *IndexBase = PushSize(Arena, IndexStoreSize);
    Assert(IndexBase);
    Assets->IndexArena = CreateArena(IndexBase, IndexStoreSize);
}

static inline void LoadAssets(assets *Assets) {
    CreatePlane(Assets, &Assets->Meshes[MESH_INDEX_TEST_OBJECT], vec3(), 8.f, 6.f, 24);
}

static inline upload_work *PushUploadWork(render_commands *Commands) {
    Assert(Commands->UploadQueueCount < UINT32_MAX - 1);
    upload_work *Result = NULL;
    if (Commands->UploadQueueCount + 1 < Commands->MaxUploadQueueCount) {
        Result = Commands->UploadQueue + Commands->UploadQueueCount;
        ++Commands->UploadQueueCount;
    }
    return Result;
}

#define PushRenderEntry(Commands, Type) (Type *)_PushRenderEntry(Commands, sizeof(Type), TYPE_##Type)
static inline render_entry_header *_PushRenderEntry(render_commands *Commands, size_t Size, render_entry_type Type) {
    render_entry_header *Result = NULL;
    if (Commands->RenderEntrySize + Size < Commands->MaxRenderEntrySize) {
        Result = Commands->Entries + Commands->RenderEntrySize;
        Commands->RenderEntrySize += Size;

        Result->Type = Type;
    }
    return Result;
}

static inline bounding_box GetMeshBoundingBox(mesh_object *Mesh) {
    vec3 Sum = vec3();
    vec3 Min = vec3(FLT_MAX);
    vec3 Max = vec3(-FLT_MAX);
    for (u32 i = 0; i < Mesh->VertexCount; ++i) {
        vec3 P = Mesh->Vertices[i].Position;
        Sum = Sum + P;
        if (P.x < Min.x) {
            Min.x = P.x;
        }
        if (P.y < Min.y) {
            Min.y = P.y;
        }
        if (P.z < Min.z) {
            Min.z = P.z;
        }
        if (P.x > Max.x) {
            Max.x = P.x;
        }
        if (P.y > Max.y) {
            Max.y = P.y;
        }
        if (P.z > Max.z) {
            Max.z = P.z;
        }
    }
    bounding_box Box = {};
    Box.Position = Sum/(f32)Mesh->VertexCount;
    Box.Bounds = Max - Min;
    return Box;
}

static inline void PushLine(render_commands *Commands, vec3 P0, vec3 P1, vec4 Color = vec4(0.f, 0.f, 0.f, 1.f)) {
    if (Commands->LineGroup.VertexCount + 2 < Commands->LineGroup.MaxVertexCount &&
        Commands->LineGroup.IndexCount + 2 < Commands->LineGroup.MaxIndexCount) {

        if (Commands->CurrentLines && !(Commands->CurrentLines->IndexCount < UINT16_MAX - 2)) {
            Commands->CurrentLines = 0;
        }

        if (!Commands->CurrentLines) {
            Commands->CurrentLines = PushRenderEntry(Commands, render_entry_line_group);
            Commands->CurrentLines->Vertices = Commands->LineGroup.Vertices + Commands->LineGroup.VertexCount;
            Commands->CurrentLines->Indices = Commands->LineGroup.Indices + Commands->LineGroup.IndexCount;
            Commands->CurrentLines->VertexCount = 0;
            Commands->CurrentLines->IndexCount = 0;
            Commands->CurrentLines->IndexOffset = Commands->LineGroup.VertexCount;
        }

        render_entry_line_group *Lines = Commands->CurrentLines;

        u32 IndexOffset = Lines->VertexCount;
        line_vertex *Vertices = Lines->Vertices + Lines->VertexCount;
        Lines->VertexCount += 2;
        Vertices[0].Position = P0;
        Vertices[0].Color = Color;
        Vertices[1].Position = P1;
        Vertices[1].Color = Color;

        u16 *Indices = Lines->Indices + Lines->IndexCount;
        Lines->IndexCount += 2;
        Indices[0] = IndexOffset;
        Indices[1] = IndexOffset + 1;

        Commands->LineGroup.VertexCount += 2;
        Commands->LineGroup.IndexCount += 2;
    }
}

static inline void DrawBoundingBox(render_commands *Commands, bounding_box Box) {
    //        7 ---- 6
    //       / |    /|
    //      0 ---- 1 |
    //      |  4 --|-5
    //      | /    |/
    //      3 ---- 2

    vec3 P0 = Box.Position + (vec3(-Box.Bounds.x, -Box.Bounds.y,  Box.Bounds.z)/2.f);
    vec3 P1 = Box.Position + (vec3( Box.Bounds.x, -Box.Bounds.y,  Box.Bounds.z)/2.f);
    vec3 P2 = Box.Position + (vec3( Box.Bounds.x, -Box.Bounds.y, -Box.Bounds.z)/2.f);
    vec3 P3 = Box.Position + (vec3(-Box.Bounds.x, -Box.Bounds.y, -Box.Bounds.z)/2.f);
    vec3 P4 = Box.Position + (vec3(-Box.Bounds.x,  Box.Bounds.y, -Box.Bounds.z)/2.f);
    vec3 P5 = Box.Position + (vec3( Box.Bounds.x,  Box.Bounds.y, -Box.Bounds.z)/2.f);
    vec3 P6 = Box.Position + (vec3( Box.Bounds.x,  Box.Bounds.y,  Box.Bounds.z)/2.f);
    vec3 P7 = Box.Position + (vec3(-Box.Bounds.x,  Box.Bounds.y,  Box.Bounds.z)/2.f);

    PushLine(Commands, P0, P1);
    PushLine(Commands, P1, P2);
    PushLine(Commands, P2, P3);
    PushLine(Commands, P3, P0);

    PushLine(Commands, P3, P4);
    PushLine(Commands, P2, P5);
    PushLine(Commands, P0, P7);
    PushLine(Commands, P1, P6);

    PushLine(Commands, P4, P5);
    PushLine(Commands, P5, P6);
    PushLine(Commands, P6, P7);
    PushLine(Commands, P7, P4);
}

static inline vec3 GetMouseWorldPosition(camera *Camera) {
    mat4 Unproject = CalculateInverseWorldTransform(Camera, (f32)GlobalScreenWidth/GlobalScreenHeight);
    f32 X = 2.f*((f32)GlobalMouseP.x/GlobalScreenWidth - 0.5f);
    f32 Y = 2.f*((f32)GlobalMouseP.y/GlobalScreenHeight - 0.5f);
    vec4 Position = Unproject*vec4(X, -Y, -1.f, 1.f);
    vec3 Result = Position.xyz/Position.w;
    return Result;
}

static inline void DrawAxes(render_commands *Commands, vec3 P) {
    PushLine(Commands, P, P + vec3(1.f, 0.f, 0.f), COLOR_RED);
    PushLine(Commands, P, P + vec3(0.f, 1.f, 0.f), COLOR_GREEN);
    PushLine(Commands, P, P + vec3(0.f, 0.f, 1.f), COLOR_BLUE);
}

static inline void PushQuad(render_commands *Commands, vec3 *Positions, vec4 *Colors, vec2 *UVs) {
    if (Commands->QuadGroup.VertexCount + 4 < Commands->QuadGroup.MaxVertexCount &&
        Commands->QuadGroup.IndexCount + 6 < Commands->QuadGroup.MaxIndexCount) {

        if (Commands->CurrentQuads && !(Commands->CurrentQuads->IndexCount < UINT16_MAX - 6)) {
            Commands->CurrentQuads = 0;
        }

        if (!Commands->CurrentQuads) {
            Commands->CurrentQuads = PushRenderEntry(Commands, render_entry_quad_group);
            Commands->CurrentQuads->Vertices = Commands->QuadGroup.Vertices + Commands->QuadGroup.VertexCount;
            Commands->CurrentQuads->Indices = Commands->QuadGroup.Indices + Commands->QuadGroup.IndexCount;
            Commands->CurrentQuads->VertexCount = 0;
            Commands->CurrentQuads->IndexCount = 0;
            Commands->CurrentQuads->IndexOffset = Commands->QuadGroup.VertexCount;
        }

        render_entry_quad_group *Quads = Commands->CurrentQuads;

        u32 IndexOffset = Quads->VertexCount;
        vertex *Vertices = Quads->Vertices + Quads->VertexCount;
        Quads->VertexCount += 4;

        u16 *Indices = Quads->Indices + Quads->IndexCount;
        Quads->IndexCount += 6;

        Vertices[0].Position = Positions[0];
        Vertices[1].Position = Positions[1];
        Vertices[2].Position = Positions[2];
        Vertices[3].Position = Positions[3];

        Vertices[0].Color = Colors[0];
        Vertices[1].Color = Colors[1];
        Vertices[2].Color = Colors[2];
        Vertices[3].Color = Colors[3];

        Vertices[0].UV = UVs[0];
        Vertices[1].UV = UVs[1];
        Vertices[2].UV = UVs[2];
        Vertices[3].UV = UVs[3];

        Indices[0] = IndexOffset + 0;
        Indices[1] = IndexOffset + 1;
        Indices[2] = IndexOffset + 2;
        Indices[3] = IndexOffset + 2;
        Indices[4] = IndexOffset + 3;
        Indices[5] = IndexOffset + 0;

        Commands->QuadGroup.VertexCount += 4;
        Commands->QuadGroup.IndexCount += 6;
    }
};

static void DrawCircle(render_commands *Commands, vec3 C, vec2 Extent, vec4 Color) {
    vec3 Positions[4] = {};
    Positions[0] = C + vec3(-Extent.x/2.f, -Extent.y/2.f, 0.f);
    Positions[1] = C + vec3( Extent.x/2.f, -Extent.y/2.f, 0.f);
    Positions[2] = C + vec3( Extent.x/2.f,  Extent.y/2.f, 0.f);
    Positions[3] = C + vec3(-Extent.x/2.f,  Extent.y/2.f, 0.f);

    vec4 Colors[4] = {};
    Colors[0] = Color;
    Colors[1] = Color;
    Colors[2] = Color;
    Colors[3] = Color;

    vec2 UVs[4] = {};
    UVs[0] = vec2(0.f, 0.f);
    UVs[1] = vec2(1.f, 0.f);
    UVs[2] = vec2(1.f, 1.f);
    UVs[3] = vec2(0.f, 1.f);

    PushQuad(Commands, Positions, Colors, UVs);
}

static inline void DestroyCircle(program_state *State, circle_object *Circle) {
    if (Circle->Prev) {
        Circle->Prev->Next = Circle->Next;
        if (Circle->Next) {
            // not the last circle in the list
            Circle->Next->Prev = Circle->Prev;
        }
    }
    else {
        // The first circle in the list
        Assert(State->FirstActiveCircle == Circle);
        State->FirstActiveCircle = Circle->Next;
        if (Circle->Next) {
            Circle->Next->Prev = NULL;
        }
    }

    if (State->HotCircle = Circle) {
        State->HotCircle = NULL;
    }

    Circle->Next = State->FirstFreeCircle;
    State->FirstFreeCircle = Circle;
    --State->CircleCount;
}

static inline circle_object *CreateCircle(program_state *State) {
    circle_object *Result = NULL;
    if (State->FirstFreeCircle) {
        Result = State->FirstFreeCircle;
        State->FirstFreeCircle = State->FirstFreeCircle->Next;
        *Result = {};
        if (State->FirstActiveCircle) {
            Result->Next = State->FirstActiveCircle;
            State->FirstActiveCircle->Prev = Result;
        }
        else {
            Result->Next = NULL;
        }
        State->FirstActiveCircle = Result;
        ++State->CircleCount;
    }
    return Result;
}

static void UpdateAndRender(program_memory *Memory, render_commands *Commands, program_input *Input, f64 Frametime) {
    program_state *State = (program_state *)Memory->PersistantMemory;
    if (!Memory->Initialized) {
        Memory->Initialized = true;
        State->PermanentArena = CreateArena(Memory->PersistantMemory, Memory->PersistantMemorySize);
        State->PermanentArena.Used = sizeof(*State);

        State->FirstFreeCircle = State->Circles;
        for (u32 i = 1; i < ArrayCount(State->Circles); i++) {
            State->Circles[i - 1].Next = State->Circles + i;
        }

        GlobalRandom = InitRandom(12);
        InitCamera(&State->Camera);
        InitAssetStore(&State->Assets, &State->PermanentArena);
        LoadAssets(&State->Assets);

        State->TestBox = GetMeshBoundingBox(&State->Assets.Meshes[MESH_INDEX_TEST_OBJECT]);

        upload_work *Work = PushUploadWork(Commands);
        if (Work) {
            Work->Index = MESH_INDEX_TEST_OBJECT;
            Work->Mesh = &State->Assets.Meshes[MESH_INDEX_TEST_OBJECT];
        }
    }
    Commands->Camera = &State->Camera;
    Commands->Assets = &State->Assets;
    Commands->WorldUp = vec3(0.f, 0.f, 1.f);

    if (ButtonDown(Input, BUTTON_KEY_ESCAPE)) {
        circle_object *Circle = State->FirstActiveCircle;
        if (Circle) {
            DestroyCircle(State, Circle);
        }
    }

    if (ButtonDown(Input, BUTTON_KEY_SPACE)) {
        circle_object *Circle = CreateCircle(State);
        if (Circle) {
            Circle->Color = vec4(RandomFloat(&GlobalRandom), RandomFloat(&GlobalRandom), RandomFloat(&GlobalRandom), .5f);
            Circle->Position = vec3(RandomRange(&GlobalRandom, -5.f, 5.f), RandomRange(&GlobalRandom, -5.f, 5.f), RandomRange(&GlobalRandom, -5.f, 5.f));
            Circle->Velocity = Normalized(vec3(RandomBilateral(&GlobalRandom), RandomBilateral(&GlobalRandom), RandomBilateral(&GlobalRandom)));
            Circle->Radius = RandomRange(&GlobalRandom, 0.35f, 1.15f);
        }
    }

    vec3 MouseP = GetMouseWorldPosition(&State->Camera);
    vec3 CameraP = State->Camera.Position;
    vec3 Ray = Normalized(MouseP - CameraP);
    vec3 N = vec3(0.f, 0.f, 1.f);

    circle_object *Circle = State->FirstActiveCircle;
    while (Circle) {
        b32 Destroy = false;
        vec4 Color = Circle->Color;
        vec3 ProjectedMouseP = vec3();
        f32 t = 0.f;

        f32 PlaneRayCosAngle = Dot(N, Ray);
        if (PlaneRayCosAngle < 0.000001f) {
            t = Dot(N, Circle->Position - CameraP)/PlaneRayCosAngle;
            ProjectedMouseP = CameraP + t*Ray;
            f32 DistanceToMouse = Magnitude(ProjectedMouseP - Circle->Position);
            if (!State->HotCircle || (Circle->Position.z > State->HotCircle->Position.z)) {
                if (DistanceToMouse < Circle->Radius) {
                    State->HotCircle = Circle;
                }
            }

            Circle->Position = Circle->Position + 0.25f*Frametime*Circle->Velocity;
            if (Circle == State->HotCircle) {
                b32 LeftClickDown = ButtonDown(Input, BUTTON_MOUSE_LEFT);
                if (DistanceToMouse > Circle->Radius && !LeftClickDown) {
                    State->HotCircle = NULL;
                }
                else {
                    if (LeftClickDown) {
                        Circle->Position = ProjectedMouseP;
                    }
                    Color = vec4(1.f);
                }
            }
        }
        DrawCircle(Commands, Circle->Position, vec2(2.f*Circle->Radius), Color);
        Circle = Circle->Next;
    }

    if (State->HotCircle) {
        if (ButtonPressed(Input, BUTTON_MOUSE_RIGHT)) {
            DestroyCircle(State, State->HotCircle);
            State->HotCircle = NULL;
        }
    }

    Commands->CircleCount = State->CircleCount;
}
