// Fragment Shader
// Physically Based Rendering (PBR)
#version 330

// shader flags
// uniform int shaderFlags; // TODO: will implement later

const int MAX_DIR_LIGHTS = 4;

// uniforms
uniform sampler2D u_albedoMap;
uniform sampler2D u_normalMap;
uniform sampler2D u_roughnessMap;
uniform sampler2D u_metalnessMap;
uniform vec3 u_lightColor;
uniform float u_roughness;
uniform float u_metalness;

uniform uint u_nLights;
uniform uint u_renderFlags;

in vec2 texCoord0;
in vec3 normal0;
//in vec3 worldPos0;
in vec3 tangentWorldPos;
in vec3 tangentCameraPos;
in vec3 tangentLightDirs[MAX_DIR_LIGHTS];
in vec3 tangentLightDiffs[MAX_DIR_LIGHTS];
in vec3 tangentNormal;

out vec4 fragColor;


// shader flag constants
const uint BASE_TEXTURE = 1u;
const uint NORMAL_MAP = 2u;
const uint ROUGHNESS_MAP = 4u;
const uint METALNESS_MAP = 8u;


// GGX/Trowbridge-Reitz normal distribution function
float D(float roughness, vec3 n, vec3 h) {
	float alpha = roughness * roughness;
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

float GeometrySchlickGGX(float dp, float roughness)
{
    float k = (roughness + 1.0) * (roughness+ 1.0) / 8.0;
    float denom = dp * (1 - k) + k;
    return dp / denom;
}

float G_Smith(float nDotL, float nDotV, float roughness){
    float ggx2  = GeometrySchlickGGX(nDotV, roughness);
    float ggx1  = GeometrySchlickGGX(nDotL, roughness);
	
    return ggx1 * ggx2;
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
	vec3 albedo = texture(u_albedoMap, texCoord0).xyz;
	vec3 n;
	if ((u_renderFlags & NORMAL_MAP) != 0u){
		n = normalize(texture(u_normalMap, texCoord0).rgb * 2.0 - vec3(1.0));
	} else {
		n = normalize(tangentNormal);
	}
	vec3 v = normalize(tangentCameraPos - tangentWorldPos);
	float metallic;
	if ((u_renderFlags & METALNESS_MAP) != 0u){
		metallic = normalize(texture(u_metalnessMap, texCoord0).r);
	} else {
	metallic = u_metalness;
	}
	float roughness;
	if ((u_renderFlags & ROUGHNESS_MAP) != 0u){
		roughness = normalize(texture(u_roughnessMap, texCoord0).r);
	} else {
	roughness = u_roughness;
	}
	vec3 Lo = vec3(0.0);
	for (uint i = 0u; i < u_nLights; i++){

		vec3 l = normalize(-tangentLightDirs[i]);
		vec3 h = normalize(v + l);

		// calc radiance here
		// for point light
		//float distance
		//float attenuation
		vec3 radiance = tangentLightDiffs[i]; // for now, we set radiance to light color
	
		// Specular
		vec3 F0 = vec3(0.04); // reflectivity at normal incidence
		F0 = mix(F0, albedo, metallic); // metallic goes here
		vec3 Ks = F(F0, v, h); // reflectivity 0.04
		vec3 Kd = 1 - Ks; // metallic goes here
		Kd *= 1.0 - metallic;

		float nDotL = max(dot(n, l), 0.0);
		float nDotV = max(dot(n, v), 0.0);

		vec3 lambert = pow(albedo, vec3(2.2));
		vec3 cookTorranceNumerator = D(roughness, n, h) * G_Smith(nDotL, nDotV, roughness) * Ks;
		float cookTorranceDenominator = 4.0 * nDotV * nDotL + 0.0001;
		//cookTorranceDenominator = max(cookTorranceDenominator, 0.000001); // prevent divide by zero

		vec3 specular = cookTorranceNumerator / cookTorranceDenominator;
		Lo += (Kd * albedo /* <-- can be lambert maybe */ / 3.14159265 + specular) * radiance * nDotL; 
	}
	// vec3 ambient = vec3(0.03) * albedo * ao;
    vec3 outLight =  Lo;

	return outLight;
}

void main()
{
	vec3 color = CalcPBRLighting();

	// gamma correction
	color = color / (color + vec3(1.0));
	color = pow(color, vec3(1.0/2.2)); 
	fragColor = vec4(color, 1.0);
	// fragColor = vec4(CalcPBRLighting(), 1.0f);
	// texture2D(u_albedoMap, texCoord0);
}
