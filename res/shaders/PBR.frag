// Fragment Shader
// Physically Based Rendering (PBR)
#version 330

// shader flags
// uniform int shaderFlags; // TODO: will implement later

// uniforms
uniform sampler2D u_albedoMap;
uniform sampler2D u_normalMap;
uniform vec3 u_lightColor;
// uniform vec3 u_lightIntensity;
uniform float u_roughness;

in vec2 texCoord0;
in vec3 normal0;
//in vec3 worldPos0;
in vec3 tangentWorldPos;
in vec3 tangentCameraPos;
in vec3 tangentLightDir;
in vec3 tangentNormal;

out vec4 fragColor;

// GGX/Trowbridge-Reitz normal distribution function
float D(float alpha, vec3 n, vec3 h) {
	float alpha2 = alpha * alpha;
	float NdotH = max(dot(n, h), 0.0);
	float NdotH2 = NdotH * NdotH;
	float denom = NdotH2 * (alpha2 - 1.0) + 1.0;
	denom = 3.14159265 * denom * denom;
	denom = max(denom, 0.000001); // prevent divide by zero

	return alpha2 / denom;
}

// Shlick-Beckmann geometry shadowing function
float G1(float alpha, vec3 n, vec3 v) {
	float NdotV = max(dot(n, v), 0.0);
	float k = alpha/2.0;
	float denom = NdotV * (1.0 - k) + k;

	denom = max(denom, 0.000001); // prevent divide by zero
	return NdotV / denom;
}

float geomSmith(float dp)
{
    float k = (u_roughness + 1.0) * (u_roughness+ 1.0) / 8.0;
    float denom = dp * (1 - k) + k;
    return dp / denom;
}

// Smith model
float G(float alpha, vec3 n, vec3 v, vec3 l) {
	return G1(alpha, n, v) * G1(alpha, n, l);
}

vec3 F(vec3 f0, vec3 v, vec3 h) {
	float VdotH = max(dot(v, h), 0.0);
	return f0 + (1 - f0) * pow(clamp(1.0 - VdotH, 0.0, 1.0), 5.0);
}

vec3 CalcPBRLighting() {
	vec3 l = normalize(-tangentLightDir);
	vec3 n = normalize(texture(u_normalMap, texCoord0).rgb * 2.0 - vec3(1.0));
	vec3 v = normalize(tangentCameraPos - tangentWorldPos);
	vec3 h = normalize(v + l);
	float alpha = u_roughness * u_roughness; 
	vec3 Ks = F(vec3(0.04), v, h); // reflectivity 0.04
	vec3 Kd = 1 - Ks; // metallic goes here

	float nDotL = max(dot(n, l), 0.0);
	float nDotV = max(dot(n, v), 0.0);

	vec3 lambert = pow(texture2D(u_albedoMap, texCoord0).xyz, vec3(2.2));
	vec3 cookTorranceNumerator = D(alpha, n, h) * G(alpha, n, v, l) * Ks;
	float cookTorranceDenominator = 4.0 * nDotV * nDotL + 0.0001;
	//cookTorranceDenominator = max(cookTorranceDenominator, 0.000001); // prevent divide by zero

	vec3 cookTorrance = cookTorranceNumerator / cookTorranceDenominator;
	vec3 BRDF = Kd * lambert / 3.14159265 + cookTorrance;
	vec3 outLight = BRDF * u_lightColor  * nDotL;

	return outLight;
}

void main()
{
	vec3 color = CalcPBRLighting();
	color = pow(color, vec3(1.0/2.2)); 
	fragColor = vec4(color, 1.0);
	// fragColor = vec4(CalcPBRLighting(), 1.0f);
	// texture2D(u_albedoMap, texCoord0);
}
