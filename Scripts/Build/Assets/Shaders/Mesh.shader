#shader vertex
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec3 a_Tangent;
layout(location = 3) in vec3 a_Bitangent;
layout(location = 4) in vec2 a_TexCoords;

uniform mat4 u_ProjectionView;
uniform mat4 u_Transform;

out vec2 v_TexCoords;

void main()
{
	v_TexCoords = a_TexCoords;
	gl_Position = u_ProjectionView * u_Transform * vec4(a_Position, 1.0f);
}

#shader fragment
#version 450 core

layout(location = 0) out vec4 o_Color;

in vec2 v_TexCoords;

void main()
{
	o_Color = vec4(0.0, 0.0, 0.0, 1.0);
}