#version 330 core

layout(location = 0) in vec3 _Position;
layout(location = 1) in vec4 _Color;

uniform mat4 Transform;

out vec4 Color;

void main() {
    Color = _Color;
    gl_Position = Transform*vec4(_Position, 1.0);
}
