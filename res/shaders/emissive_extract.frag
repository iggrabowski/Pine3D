#version 330 core

in vec2 v_texCoords;

out vec4 fragColor;

uniform sampler2D u_emissiveMap;

void main() {
    vec4 emissiveColor = texture(u_emissiveMap, v_texCoords);

    fragColor = emissiveColor;
}
