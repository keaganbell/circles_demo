#version 330 core

in vec4 Color;
in vec2 UV;

uniform float Radius;

out vec4 FragColor;

void main() {
    vec2 P = 2.0f*UV - vec2(1.0f);
    if (sqrt(dot(P, P)) > Radius) {
        discard;
    }
    FragColor = Color;
}

