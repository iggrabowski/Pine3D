#version 130

attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normal;

out vec2 texCoord0;
out vec3 normal0;

uniform mat4 MVP;
uniform mat4 Model;

void main()
{
	gl_Position = MVP * vec4(position, 1.0);
	texCoord0 = texCoord;
	normal0 = (Model * vec4(normal, 0.0)).xyz;
}
