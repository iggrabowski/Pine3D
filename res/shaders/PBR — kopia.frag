// Fragment Shader
// Physically Based Rendering (PBR)
#version 130

// shader flags
uniform int shaderFlags; // TODO: will implement later

// uniforms
uniform sampler2D u_albedoMap;
uniform sampler2D u_normalMap;
uniform vec3 u_cameraPosition;
uniform vec3 u_lightDir; // for now just 1 light directional
uniform vec3 u_lightColor;
uniform vec3 u_lightIntensity;
uniform float u_roughness;

in vec2 texCoord0;
in vec3 normal0;
in mat3 TBN; // Tangent-Bitangent-Normal matrix
in vec3 worldPos0;

out vec4 fragColor;

// GGX/Trowbridge-Reitz normal distribution function
float D(float roughness, vec3 n, vec3 h) {
	float alpha = roughness * roughness;
	float alpha2 = a * a;
	float 
	float NdotH2 = NdotH * NdotH;
	float denom = (NdotH2 * (a2 - 1.0) + 1.0);
	denom = 3.14159265 * denom * denom;
	return a2 / denom;
})

vec3 CalcPBRLighting() {
	vec3 l = normalize(-u_lightDir);
	vec3 n = normalize(texture2D(u_normalMap, texCoord0));
	vec3 v = normalize(u_cameraPosition - fragPos);
	vec3 h = normalize(v + l);
}

void main()
{
	vec3 N = normalize(normal);
	vec3 

	fragColor = texture2D(u_AlbedoMap, texCoord0);
}
