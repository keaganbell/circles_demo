#version 330 core

layout(location = 0) in vec3 _Position;
layout(location = 1) in vec4 _Color;
layout(location = 2) in vec2 _UV;

uniform mat4 Transform;

out vec4 Color;
out vec2 UV;

void main() {
    Color = _Color;
    UV = _UV;
    gl_Position = Transform*vec4(_Position, 1.0);
}
