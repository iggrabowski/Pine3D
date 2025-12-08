#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;

out vec2 texCoord0;
out vec3 normal0;
out vec3 worldPos0;
out vec3 tangentWorldPos;
out vec3 tangentCameraPos;
out vec3 tangentLightDir;
out vec3 tangentNormal;
out mat3 TBN;

uniform mat4 MVP;
uniform mat4 Model;
uniform vec3 u_cameraPos;
uniform vec3 u_lightDir; // for now just 1 light directional

void main()
{
	vec3 T = normalize(vec3(Model * vec4(tangent,   0.0)));
	vec3 B = normalize(vec3(Model * vec4(bitangent, 0.0)));
	vec3 N = normalize(vec3(Model * vec4(normal,    0.0)));
	TBN = mat3(T, B, N);
	vec4 worldPos = Model * vec4(position, 1.0);
	worldPos0 =			worldPos.xyz;
	tangentWorldPos =	transpose(TBN) * worldPos.xyz;
	tangentNormal =		transpose(TBN) * normal;
	tangentCameraPos =	transpose(TBN) * u_cameraPos;
	tangentLightDir =	transpose(TBN) * u_lightDir;
	gl_Position = MVP * vec4(position, 1.0);
	texCoord0 = texCoord;
	normal0 = (Model * vec4(normal, 0.0)).xyz;
	tangentNormal =		transpose(TBN) * normal0;
}
