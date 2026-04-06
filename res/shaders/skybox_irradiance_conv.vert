#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 u_Projection;
uniform mat4 u_View;

out vec3 localPos;

void main()
{
    localPos = aPos;

    // remove translation from the view matrix so capture is centered
    mat4 rotView = mat4(mat3(u_View));
    gl_Position = u_Projection * rotView * vec4(localPos, 1.0);
}