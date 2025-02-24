#pragma once
#define GL_DEBUG_OUTPUT                   0x92E0
#define GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB   0x8242

#define GL_NUM_EXTENSIONS                 0x821D

#define GL_MAX_COLOR_ATTACHMENTS          0x8CDF
#define GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS 0x8B4D

#define GL_TEXTURE_3D                     0x806F

#define GL_TEXTURE0                       0x84C0
#define GL_TEXTURE1                       0x84C1
#define GL_TEXTURE2                       0x84C2
#define GL_TEXTURE3                       0x84C3
#define GL_TEXTURE4                       0x84C4
#define GL_TEXTURE5                       0x84C5
#define GL_TEXTURE6                       0x84C6
#define GL_TEXTURE7                       0x84C7

#define GL_DEBUG_SEVERITY_HIGH            0x9146
#define GL_DEBUG_SEVERITY_MEDIUM          0x9147
#define GL_DEBUG_SEVERITY_LOW             0x9148
#define GL_DEBUG_TYPE_MARKER              0x8268
#define GL_DEBUG_TYPE_PUSH_GROUP          0x8269
#define GL_DEBUG_TYPE_POP_GROUP           0x826A
#define GL_DEBUG_SEVERITY_NOTIFICATION    0x826B
#define GL_DEBUG_SEVERITY_HIGH_ARB        0x9146
#define GL_DEBUG_SEVERITY_MEDIUM_ARB      0x9147
#define GL_DEBUG_SEVERITY_LOW_ARB         0x9148
#define GL_DEBUG_OUTPUT_SYNCHRONOUS       0x8242

#define GL_VERTEX_ARRAY_BINDING           0x85B5
#define GL_VERTEX_BINDING_BUFFER          0x8F4F
#define GL_ARRAY_BUFFER_BINDING           0x8894
#define GL_ELEMENT_ARRAY_BUFFER_BINDING   0x8895

#define GL_ARRAY_BUFFER                   0x8892
#define GL_ELEMENT_ARRAY_BUFFER           0x8893
#define GL_STREAM_DRAW                    0x88E0
#define GL_STREAM_READ                    0x88E1
#define GL_STREAM_COPY                    0x88E2
#define GL_STATIC_DRAW                    0x88E4
#define GL_STATIC_READ                    0x88E5
#define GL_STATIC_COPY                    0x88E6
#define GL_DYNAMIC_DRAW                   0x88E8
#define GL_DYNAMIC_READ                   0x88E9
#define GL_DYNAMIC_COPY                   0x88EA

#define GL_CLAMP_TO_EDGE                  0x812F
#define GL_TEXTURE_MIN_LOD                0x813A
#define GL_TEXTURE_MAX_LOD                0x813B
#define GL_TEXTURE_BASE_LEVEL             0x813C
#define GL_TEXTURE_MAX_LEVEL              0x813D
#define GL_TEXTURE_WRAP_R                 0x8072

#define GL_FRAMEBUFFER_SRGB               0x8DB9
#define GL_SRGB8_ALPHA8                   0x8C43

#define GL_SHADING_LANGUAGE_VERSION       0x8B8C
#define GL_FRAGMENT_SHADER                0x8B30
#define GL_VERTEX_SHADER                  0x8B31
#define GL_COMPILE_STATUS                 0x8B81
#define GL_LINK_STATUS                    0x8B82
#define GL_VALIDATE_STATUS                0x8B83

#define GL_TEXTURE_2D_ARRAY               0x8C1A

#define GL_FRAMEBUFFER                    0x8D40
#define GL_READ_FRAMEBUFFER               0x8CA8
#define GL_DRAW_FRAMEBUFFER               0x8CA9
#define GL_COLOR_ATTACHMENT0              0x8CE0
#define GL_COLOR_ATTACHMENT1              0x8CE1
#define GL_COLOR_ATTACHMENT2              0x8CE2
#define GL_COLOR_ATTACHMENT3              0x8CE3
#define GL_COLOR_ATTACHMENT4              0x8CE4
#define GL_COLOR_ATTACHMENT5              0x8CE5
#define GL_COLOR_ATTACHMENT6              0x8CE6
#define GL_COLOR_ATTACHMENT7              0x8CE7
#define GL_COLOR_ATTACHMENT8              0x8CE8
#define GL_COLOR_ATTACHMENT9              0x8CE9
#define GL_COLOR_ATTACHMENT10             0x8CEA
#define GL_COLOR_ATTACHMENT11             0x8CEB
#define GL_COLOR_ATTACHMENT12             0x8CEC
#define GL_COLOR_ATTACHMENT13             0x8CED
#define GL_COLOR_ATTACHMENT14             0x8CEE
#define GL_COLOR_ATTACHMENT15             0x8CEF
#define GL_COLOR_ATTACHMENT16             0x8CF0
#define GL_COLOR_ATTACHMENT17             0x8CF1
#define GL_COLOR_ATTACHMENT18             0x8CF2
#define GL_COLOR_ATTACHMENT19             0x8CF3
#define GL_COLOR_ATTACHMENT20             0x8CF4
#define GL_COLOR_ATTACHMENT21             0x8CF5
#define GL_COLOR_ATTACHMENT22             0x8CF6
#define GL_COLOR_ATTACHMENT23             0x8CF7
#define GL_COLOR_ATTACHMENT24             0x8CF8
#define GL_COLOR_ATTACHMENT25             0x8CF9
#define GL_COLOR_ATTACHMENT26             0x8CFA
#define GL_COLOR_ATTACHMENT27             0x8CFB
#define GL_COLOR_ATTACHMENT28             0x8CFC
#define GL_COLOR_ATTACHMENT29             0x8CFD
#define GL_COLOR_ATTACHMENT30             0x8CFE
#define GL_COLOR_ATTACHMENT31             0x8CFF
#define GL_DEPTH_ATTACHMENT               0x8D00
#define GL_FRAMEBUFFER_COMPLETE           0x8CD5

#define GL_RENDERBUFFER                   0x8D41

#define GL_DEPTH_COMPONENT16              0x81A5
#define GL_DEPTH_COMPONENT24              0x81A6
#define GL_DEPTH_COMPONENT32              0x81A7
#define GL_DEPTH_COMPONENT32F             0x8CAC

#define GL_RED_INTEGER                    0x8D94
#define GL_GREEN_INTEGER                  0x8D95
#define GL_BLUE_INTEGER                   0x8D96

#define GL_RGBA32F                        0x8814
#define GL_RGB32F                         0x8815
#define GL_RGBA16F                        0x881A
#define GL_RGB16F                         0x881B
#define GL_R8                             0x8229
#define GL_R16                            0x822A
#define GL_RG8                            0x822B
#define GL_RG16                           0x822C
#define GL_R16F                           0x822D
#define GL_R32F                           0x822E
#define GL_RG16F                          0x822F
#define GL_RG32F                          0x8230
#define GL_R8I                            0x8231
#define GL_R8UI                           0x8232
#define GL_R16I                           0x8233
#define GL_R16UI                          0x8234
#define GL_R32I                           0x8235
#define GL_R32UI                          0x8236
#define GL_RG8I                           0x8237
#define GL_RG8UI                          0x8238
#define GL_RG16I                          0x8239
#define GL_RG16UI                         0x823A
#define GL_RG32I                          0x823B
#define GL_RG32UI                         0x823C
#define GL_R11F_G11F_B10F                 0x8C3A

#define GL_MULTISAMPLE                    0x809D
#define GL_SAMPLE_ALPHA_TO_COVERAGE       0x809E
#define GL_SAMPLE_ALPHA_TO_ONE            0x809F
#define GL_SAMPLE_COVERAGE                0x80A0
#define GL_SAMPLE_BUFFERS                 0x80A8
#define GL_SAMPLES                        0x80A9
#define GL_SAMPLE_COVERAGE_VALUE          0x80AA
#define GL_SAMPLE_COVERAGE_INVERT         0x80AB
#define GL_TEXTURE_2D_MULTISAMPLE         0x9100
#define GL_MAX_SAMPLES                    0x8D57
#define GL_MAX_COLOR_TEXTURE_SAMPLES      0x910E
#define GL_MAX_DEPTH_TEXTURE_SAMPLES      0x910F

typedef char GLchar;
typedef ptrdiff_t GLsizeiptr;
typedef ptrdiff_t GLintptr;

typedef GLuint gl_create_shader(GLenum type);
typedef void   gl_delete_shader(GLuint shader);
typedef void   gl_shader_source(GLuint shader, GLsizei count, GLchar **string, GLint *length);
typedef void   gl_compile_shader(GLuint shader);
typedef void   gl_get_shader_info_log(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef void   gl_get_shaderiv(GLuint shader, GLenum pname, GLint *params);
static gl_create_shader *glCreateShader;
static gl_delete_shader *glDeleteShader;
static gl_shader_source *glShaderSource;
static gl_compile_shader *glCompileShader;
static gl_get_shader_info_log *glGetShaderInfoLog;
static gl_get_shaderiv *glGetShaderiv;

typedef GLuint gl_create_program(void);
typedef void   gl_delete_program (GLuint program);
typedef void   gl_attach_shader(GLuint program, GLuint shader);
typedef void   gl_link_program(GLuint program);
typedef void   gl_use_program(GLuint program);
typedef void   gl_validate_program(GLuint program);
typedef void   gl_get_program_info_log(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef void   gl_get_programiv(GLuint program, GLenum pname, GLint *params);
static gl_create_program *glCreateProgram;
static gl_delete_program *glDeleteProgram;
static gl_attach_shader *glAttachShader;
static gl_link_program *glLinkProgram;
static gl_use_program *glUseProgram;
static gl_validate_program *glValidateProgram;
static gl_get_program_info_log *glGetProgramInfoLog;
static gl_get_programiv *glGetProgramiv;

typedef GLint gl_get_uniform_location(GLuint program, const GLchar *name);
typedef void  gl_uniform_matrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void  gl_uniform1i(GLint location, GLint v0);
typedef void  gl_uniform1f(GLint location, GLfloat v0);
typedef void  gl_uniform2fv(GLint location, GLsizei count, const GLfloat *value);
typedef void  gl_uniform3fv(GLint location, GLsizei count, const GLfloat *value);
typedef void  gl_uniform4fv(GLint location, GLsizei count, const GLfloat *value);
static gl_get_uniform_location *glGetUniformLocation;
static gl_uniform_matrix4fv *glUniformMatrix4fv;
static gl_uniform1i *glUniform1i;
static gl_uniform1f *glUniform1f;
static gl_uniform2fv *glUniform2fv;
static gl_uniform3fv *glUniform3fv;
static gl_uniform4fv *glUniform4fv;

typedef void gl_gen_vertex_arrays(GLsizei n, GLuint *arrays);
typedef void gl_bind_vertex_array(GLuint array);
typedef void gl_gen_buffers(GLsizei n, GLuint *buffers);
typedef void gl_bind_buffer(GLenum target, GLuint buffer);
typedef void gl_buffer_data(GLenum target, GLsizeiptr size, const void *data, GLenum usage);
typedef void gl_buffer_sub_data(GLenum target, GLintptr offset, GLsizeiptr size, const void *data);
static gl_gen_vertex_arrays *glGenVertexArrays;
static gl_bind_vertex_array *glBindVertexArray;
static gl_gen_buffers *glGenBuffers;
static gl_bind_buffer *glBindBuffer;
static gl_buffer_data *glBufferData;
static gl_buffer_sub_data *glBufferSubData;

typedef void gl_draw_elements_base_vertex(GLenum mode, GLsizei count, GLenum type, GLvoid *indices, GLint basevertex);
static gl_draw_elements_base_vertex *glDrawElementsBaseVertex;

typedef GLint gl_get_attrib_location(GLuint program, const GLchar *name);
typedef void  gl_bind_attrib_location(GLuint program, GLuint index, const GLchar *name);
typedef void  gl_enable_vertex_attrib_array(GLuint index);
typedef void  gl_disable_vertex_attrib_array(GLuint index);
typedef void  gl_vertex_attrib_pointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
typedef void  gl_vertex_attribi_pointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer);
static gl_get_attrib_location *glGetAttribLocation;
static gl_bind_attrib_location *glBindAttribLocation;
static gl_enable_vertex_attrib_array *glEnableVertexAttribArray;
static gl_disable_vertex_attrib_array *glDisableVertexAttribArray;
static gl_vertex_attrib_pointer *glVertexAttribPointer;
static gl_vertex_attribi_pointer *glVertexAttribIPointer;

typedef void gl_gen_framebuffers(GLsizei n, GLuint *framebuffers);
typedef void gl_bind_framebuffer(GLenum target, GLuint buffer);
typedef void gl_framebuffer_texture_2d(	GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef GLenum gl_check_framebuffer_status(GLenum target);
typedef void gl_tex_image_2d_multisample(GLenum target, GLsizei samples, GLint internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
typedef void gl_blit_framebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
static gl_gen_framebuffers *glGenFramebuffers;
static gl_bind_framebuffer *glBindFramebuffer;
static gl_framebuffer_texture_2d *glFramebufferTexture2D;
static gl_check_framebuffer_status *glCheckFramebufferStatus;
static gl_tex_image_2d_multisample *glTexImage2DMultisample;
static gl_blit_framebuffer *glBlitFramebuffer;

typedef void gl_gen_render_buffers(GLsizei n, GLuint *renderbuffers);
typedef void gl_bind_renderbuffer(GLenum target, GLuint renderbuffer);
typedef void gl_render_buffer_storage_multisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
typedef void gl_framebuffer_renderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
static gl_gen_render_buffers *glGenRenderbuffers;
static gl_bind_renderbuffer *glBindRenderbuffer;
static gl_render_buffer_storage_multisample *glRenderbufferStorageMultisample;
static gl_framebuffer_renderbuffer *glFramebufferRenderbuffer;

typedef void debug_callback(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
typedef void gl_debug_message_callback(debug_callback callback, const void *userParam);
static gl_debug_message_callback *glDebugMessageCallback;
