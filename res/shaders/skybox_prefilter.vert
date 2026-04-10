#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 u_projection;
uniform mat4 u_view;

out vec3 localPos;

void main()
{
    localPos = aPos;

    // remove translation from the view matrix so capture is centered
    mat4 rotView = mat4(mat3(u_view));
    gl_Position = u_projection * rotView * vec4(localPos, 1.0);
}