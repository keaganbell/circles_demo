#pragma once

#define WGL_CONTEXT_MAJOR_VERSION_ARB           0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB           0x2092
#define WGL_CONTEXT_LAYER_PLANE_ARB             0x2093
#define WGL_CONTEXT_FLAGS_ARB                   0x2094
#define WGL_CONTEXT_PROFILE_MASK_ARB            0x9126
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB  0x0002
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB    0x00000001
#define WGL_CONTEXT_DEBUG_BIT_ARB           0x00000001

typedef HGLRC WINAPI wgl_create_context_attribs_arb(HDC DC, HGLRC SharedContext, i32 *Attribs);
typedef void WINAPI wgl_swap_interval_ext(u32 Interval);

static opengl *WindowsInitOpenGL(HDC DC) {
    opengl *OpenGL = NULL;

    // TODO: TLC on pixel format for sRGB
    PIXELFORMATDESCRIPTOR DesiredPixelFormat = {};
    DesiredPixelFormat.nSize      = sizeof(PIXELFORMATDESCRIPTOR);
    DesiredPixelFormat.nVersion   = 1;
    DesiredPixelFormat.dwFlags    = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    DesiredPixelFormat.iPixelType = PFD_TYPE_RGBA;
    DesiredPixelFormat.cColorBits = 24;
    DesiredPixelFormat.cAlphaBits = 8;
    DesiredPixelFormat.iLayerType = PFD_MAIN_PLANE;

    i32 SuggestedPixelFormatIndex = ChoosePixelFormat(DC, &DesiredPixelFormat);
    PIXELFORMATDESCRIPTOR SuggestedPixelFormat = {};
    DescribePixelFormat(DC, SuggestedPixelFormatIndex, sizeof(SuggestedPixelFormat), &SuggestedPixelFormat);
    SetPixelFormat(DC, SuggestedPixelFormatIndex, &SuggestedPixelFormat);

    HGLRC RC = wglCreateContext(DC);
    if (wglMakeCurrent(DC, RC)) {
        wgl_create_context_attribs_arb *wglCreateContextAttribsARB = (wgl_create_context_attribs_arb *)wglGetProcAddress("wglCreateContextAttribsARB");
        if (wglCreateContextAttribsARB) {
            i32 Attribs[] = {
                WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
                WGL_CONTEXT_MINOR_VERSION_ARB, 3,
                WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_DEBUG_BIT_ARB,
                WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
                0
            };
            HGLRC ShareContext = 0;
            HGLRC ModernRC = wglCreateContextAttribsARB(DC, ShareContext, Attribs);
            if (ModernRC) {
                wglMakeCurrent(DC, ModernRC);
                wglDeleteContext(RC);
                RC = ModernRC;

                wgl_swap_interval_ext *wglSwapIntervalEXT = (wgl_swap_interval_ext *)wglGetProcAddress("wglSwapIntervalEXT");
                if (wglSwapIntervalEXT) {
                    wglSwapIntervalEXT(1);
                }
                else {
                    LINFO("No VSync support.");
                }

                glCreateShader = (gl_create_shader *)wglGetProcAddress("glCreateShader");
                glDeleteShader = (gl_delete_shader *)wglGetProcAddress("glDeleteShader");
                glShaderSource = (gl_shader_source *)wglGetProcAddress("glShaderSource");
                glCompileShader = (gl_compile_shader *)wglGetProcAddress("glCompileShader");
                glGetShaderInfoLog = (gl_get_shader_info_log *)wglGetProcAddress("glGetShaderInfoLog");
                glGetShaderiv = (gl_get_shaderiv *)wglGetProcAddress("glGetShaderiv");

                glCreateProgram = (gl_create_program *)wglGetProcAddress("glCreateProgram");
                glDeleteProgram = (gl_delete_program *)wglGetProcAddress("glDeleteProgram");
                glAttachShader = (gl_attach_shader *)wglGetProcAddress("glAttachShader");
                glLinkProgram = (gl_link_program *)wglGetProcAddress("glLinkProgram");
                glUseProgram = (gl_use_program *)wglGetProcAddress("glUseProgram");
                glValidateProgram = (gl_validate_program *)wglGetProcAddress("glValidateProgram");
                glGetProgramInfoLog = (gl_get_program_info_log *)wglGetProcAddress("glGetProgramInfoLog");
                glGetProgramiv = (gl_get_programiv *)wglGetProcAddress("glGetProgramiv");

                glGetUniformLocation = (gl_get_uniform_location *)wglGetProcAddress("glGetUniformLocation");
                glUniformMatrix4fv = (gl_uniform_matrix4fv *)wglGetProcAddress("glUniformMatrix4fv");
                glUniform1i = (gl_uniform1i *)wglGetProcAddress("glUniform1i");
                glUniform1f = (gl_uniform1f *)wglGetProcAddress("glUniform1f");
                glUniform2fv = (gl_uniform2fv *)wglGetProcAddress("glUniform2fv");
                glUniform3fv = (gl_uniform3fv *)wglGetProcAddress("glUniform3fv");
                glUniform4fv = (gl_uniform4fv *)wglGetProcAddress("glUniform4fv");

                glGenVertexArrays = (gl_gen_vertex_arrays *)wglGetProcAddress("glGenVertexArrays");
                glBindVertexArray = (gl_bind_vertex_array *)wglGetProcAddress("glBindVertexArray");
                glGenBuffers = (gl_gen_buffers *)wglGetProcAddress("glGenBuffers");
                glBindBuffer = (gl_bind_buffer *)wglGetProcAddress("glBindBuffer");
                glBufferData = (gl_buffer_data *)wglGetProcAddress("glBufferData");
                glBufferSubData = (gl_buffer_sub_data *)wglGetProcAddress("glBufferSubData");

                glDrawElementsBaseVertex = (gl_draw_elements_base_vertex *)wglGetProcAddress("glDrawElementsBaseVertex");

                glGetAttribLocation = (gl_get_attrib_location *)wglGetProcAddress("glGetAttribLocation");
                glBindAttribLocation = (gl_bind_attrib_location *)wglGetProcAddress("glBindAttribLocation");
                glEnableVertexAttribArray = (gl_enable_vertex_attrib_array *)wglGetProcAddress("glEnableVertexAttribArray");
                glDisableVertexAttribArray = (gl_disable_vertex_attrib_array *)wglGetProcAddress("glDisableVertexAttribArray");
                glVertexAttribPointer = (gl_vertex_attrib_pointer *)wglGetProcAddress("glVertexAttribPointer");
                glVertexAttribIPointer = (gl_vertex_attribi_pointer *)wglGetProcAddress("glVertexAttribIPointer");

                glGenFramebuffers = (gl_gen_framebuffers *)wglGetProcAddress("glGenFramebuffers");
                glBindFramebuffer = (gl_bind_framebuffer *)wglGetProcAddress("glBindFramebuffer");
                glFramebufferTexture2D = (gl_framebuffer_texture_2d *)wglGetProcAddress("glFramebufferTexture2D");
                glCheckFramebufferStatus = (gl_check_framebuffer_status *)wglGetProcAddress("glCheckFramebufferStatus");
                glTexImage2DMultisample = (gl_tex_image_2d_multisample *)wglGetProcAddress("glTexImage2DMultisample");
                glBlitFramebuffer = (gl_blit_framebuffer *)wglGetProcAddress("glBlitFramebuffer");

                glGenRenderbuffers = (gl_gen_render_buffers *)wglGetProcAddress("glGenRenderbuffers");
                glBindRenderbuffer = (gl_bind_renderbuffer *)wglGetProcAddress("glBindRenderbuffer");
                glRenderbufferStorageMultisample = (gl_render_buffer_storage_multisample *)wglGetProcAddress("glRenderbufferStorageMultisample");
                glFramebufferRenderbuffer = (gl_framebuffer_renderbuffer *)wglGetProcAddress("glFramebufferRenderbuffer");

                glDebugMessageCallback = (gl_debug_message_callback *)wglGetProcAddress("glDebugMessageCallback");

                size_t OpenGLSize = sizeof(opengl);
                OpenGL = (opengl *)PlatformAllocate(OpenGLSize);
                InitOpenGL(OpenGL);
            }
            else {
                LERROR("Could not create modern OpenGL rendering context.");
            }
        }
        else {
            LERROR("wglCreateContextAttribsARB not found.");
        }
    }
    else {
        LERROR("Failed to create OpenGL context.");
    }
    return OpenGL;
}
