#shader vertex
#version 450

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec3 a_Tangent;
layout(location = 3) in vec3 a_Bitangent;
layout(location = 4) in vec2 a_TexCoords;

uniform mat4 u_ProjectionView;
uniform mat4 u_Transform;

out VertexShaderOutput
{
	vec3 WorldPosition;
	vec3 Normal;
	vec2 TexCoord;
	mat3 WorldNormals;
	mat3 WorldTransform;
	vec3 Bitangent;
} vs_Output;

void main()
{
	vs_Output.WorldPosition = vec3(u_Transform * vec4(a_Position, 1.0));
	vs_Output.Normal = mat3(u_Transform) * a_Normal;
	vs_Output.TexCoord = vec2(a_TexCoords.x, 1.0 - a_TexCoords.y);
	vs_Output.WorldNormals = mat3(u_Transform) * mat3(a_Tangent, a_Bitangent, a_Normal);
	vs_Output.WorldTransform = mat3(u_Transform);
	vs_Output.Bitangent = a_Bitangent;

	gl_Position = u_ProjectionView * u_Transform * vec4(a_Position, 1.0f);
}

#shader fragment
#version 430

const float PI = 3.141592;
const float Epsilon = 0.00001;

const int LightCount = 1;

// Constant normal incidence Fresnel factor for all dielectrics.
const vec3 Fdielectric = vec3(0.04);

struct DirectionalLight
{
	vec3 Direction;
	vec3 Radiance;
	float Multiplier;
};

in VertexShaderOutput
{
	vec3 WorldPosition;
	vec3 Normal;
	vec2 TexCoord;
	mat3 WorldNormals;
	mat3 WorldTransform;
	vec3 Bitangent;
} vs_Input;

layout(location = 0) out vec4 color;

uniform DirectionalLight u_DirectionalLights;
uniform vec3 u_CameraPosition;

uniform vec3 u_AlbedoColor;
uniform float u_Metalness;
uniform float u_Roughness;


struct PBRParameters
{
	vec3 Albedo;
	float Roughness;
	float Metalness;

	vec3 Normal;
	vec3 View;
	float NdotV;
};
PBRParameters m_Params;

float ndfGGX(float cosLh, float roughness)
{
	float alpha = roughness * roughness;
	float alphaSq = alpha * alpha;

	float denom = (cosLh * cosLh) * (alphaSq - 1.0) + 1.0;
	return alphaSq / (PI * denom * denom);
}

float gaSchlickG1(float cosTheta, float k)
{
	return cosTheta / (cosTheta * (1.0 - k) + k);
}
float gaSchlickGGX(float cosLi, float NdotV, float roughness)
{
	float r = roughness + 1.0;
	float k = (r * r) / 8.0; // Epic suggests using this roughness remapping for analytic lights.
	return gaSchlickG1(cosLi, k) * gaSchlickG1(NdotV, k);
}

vec3 fresnelSchlick(vec3 F0, float cosTheta)
{
	return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}
vec3 fresnelSchlickRoughness(vec3 F0, float cosTheta, float roughness)
{
	return F0 + (max(vec3(1.0 - roughness), F0) - F0) * pow(1.0 - cosTheta, 5.0);
}

vec3 ApplyLighting(vec3 F0)
{
	vec3 result = vec3(0.0);
	for (int i = 0; i < LightCount; i++)
	{
		vec3 Li = u_DirectionalLights.Direction;
		vec3 Lradiance = u_DirectionalLights.Radiance * u_DirectionalLights.Multiplier;
		vec3 Lh = normalize(Li + m_Params.View);

		// Calculate angles between surface normal and various light vectors.
		float cosLi = max(0.0, dot(m_Params.Normal, Li));
		float cosLh = max(0.0, dot(m_Params.Normal, Lh));

		vec3 F = fresnelSchlick(F0, max(0.0, dot(Lh, m_Params.View)));
		float D = ndfGGX(cosLh, m_Params.Roughness);
		float G = gaSchlickGGX(cosLi, m_Params.NdotV, m_Params.Roughness);

		vec3 kd = (1.0 - F) * (1.0 - m_Params.Metalness);
		vec3 diffuseBRDF = kd * m_Params.Albedo;

		// Cook-Torrance
		vec3 specularBRDF = (F * D * G) / max(Epsilon, 4.0 * cosLi * m_Params.NdotV);

		result += (diffuseBRDF + specularBRDF) * Lradiance * cosLi;
	}
	return result;
}

vec3 ApplyIBL(vec3 F0, vec3 Lr)
{
	// TODO: Replace with proper IBL
	return vec3(0.1) * m_Params.Albedo;
}

void main()
{
	// Standard PBR inputs
	m_Params.Albedo = u_AlbedoColor;
	m_Params.Metalness = u_Metalness;
	m_Params.Roughness = max(u_Roughness, 0.05);

	// TODO: Normal map
	m_Params.Normal = normalize(vs_Input.Normal);

	m_Params.View = normalize(u_CameraPosition - vs_Input.WorldPosition);
	m_Params.NdotV = max(dot(m_Params.Normal, m_Params.View), 0.0);

	// Specular reflection vector
	vec3 Lr = 2.0 * m_Params.NdotV * m_Params.Normal - m_Params.View;

	// Fresnel reflectance, metals use albedo
	vec3 F0 = mix(Fdielectric, m_Params.Albedo, m_Params.Metalness);

	vec3 lightContribution = ApplyLighting(F0);
	vec3 iblContribution = ApplyIBL(F0, Lr);

	color = vec4(lightContribution + iblContribution, 1.0);
}