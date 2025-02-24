#version 330 core

layout(location = 0) in vec2 _Position;
layout(location = 1) in vec2 _UV;

out vec2 UV;

void main() {
    UV = _UV;
    gl_Position = vec4(_Position, 0.0, 1.0);
}

