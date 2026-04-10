#version 330 core
in vec3 localPos;
out vec4 FragColor;

uniform samplerCube u_environmentMap;
uniform float u_roughness;
uniform uint u_sampleCount = 4096u;
uniform uint u_envResolution;

const float PI = 3.14159265359;


float RadicalInverse_VdC(uint bits) {
    bits = (bits << 16u) | (bits >> 16u);
    bits = ((bits & 0x55555555u) << 1u) | ((bits & 0xAAAAAAAAu) >> 1u);
    bits = ((bits & 0x33333333u) << 2u) | ((bits & 0xCCCCCCCCu) >> 2u);
    bits = ((bits & 0x0F0F0F0Fu) << 4u) | ((bits & 0xF0F0F0F0u) >> 4u);
    bits = ((bits & 0x00FF00FFu) << 8u) | ((bits & 0xFF00FF00u) >> 8u);
    return float(bits) * 2.3283064365386963e-10; // / 0x100000000
}

vec2 Hammersley(uint i, uint N) {
    return vec2(float(i)/float(N), RadicalInverse_VdC(i));
}

vec3 ImportanceSampleGGX(vec2 Xi, vec3 N, float roughness) {
    float a = roughness*roughness;
    float phi = 2.0 * PI * Xi.x;
    float cosTheta = sqrt( (1.0 - Xi.y) / (1.0 + (a*a - 1.0) * Xi.y) );
    float sinTheta = sqrt(max(0.0, 1.0 - cosTheta*cosTheta));
    vec3 H;
    H.x = cos(phi) * sinTheta;
    H.y = sin(phi) * sinTheta;
    H.z = cosTheta;

    vec3 up = abs(N.z) < 0.999 ? vec3(0.0,0.0,1.0) : vec3(1.0,0.0,0.0);
    vec3 tangent = normalize(cross(up, N));
    vec3 bitangent = cross(N, tangent);
    vec3 sampleVec = tangent * H.x + bitangent * H.y + N * H.z;
    return normalize(sampleVec);
}

float DistributionGGX(vec3 N, vec3 H, float roughness) {
    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH * NdotH;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    return a2 / (3.14159265 * denom * denom + 1e-6);
}

void main() {
    vec3 N = normalize(localPos);
    vec3 R = N;
    vec3 V = R;
    float totalWeight = 0.0;
    vec3 prefilteredColor = vec3(0.0);

    for(uint i = 0u; i < u_sampleCount; ++i) {
        vec2 Xi = Hammersley(i, u_sampleCount);
        vec3 H = ImportanceSampleGGX(Xi, N, u_roughness);
        vec3 L = normalize(2.0 * dot(V, H) * H - V);
        float NdotL = max(dot(N, L), 0.0);
        if(NdotL > 0.0) {
            float NdotH = max(dot(N, H), 0.0);
            float HdotV = max(dot(H, V), 0.0);
            float D = DistributionGGX(N, H, u_roughness);
            float pdf = (D * NdotH) / (4.0 * HdotV + 1e-6);

            float resolution = float(u_envResolution);
            float saTexel = 4.0 * 3.14159265359 / (6.0 * resolution * resolution);
            float saSample = 1.0 / (float(u_sampleCount) * pdf + 1e-6);
            float mip = 0.0;
            if(u_roughness > 0.0) {
                mip = 0.5 * log2(saSample / saTexel);
                mip = max(mip, 0.0);
        }

        vec3 sampleColor = textureLod(u_environmentMap, L, mip).rgb;
        prefilteredColor += sampleColor * NdotL;
        totalWeight += NdotL;
        }
    }

    prefilteredColor = prefilteredColor / max(totalWeight, 0.0001);
    FragColor = vec4(prefilteredColor, 1.0);
}