#shader vertex
#version 450 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoords;
layout(location = 3) in float a_TexIndex;

out vec4 v_Color;
out vec2 v_TexCoords;
out flat float v_TexIndex;

uniform mat4 u_ProjectionView;

void main()
{
	v_Color = a_Color;
	v_TexCoords = a_TexCoords;
	v_TexIndex = a_TexIndex;

	gl_Position = u_ProjectionView * a_Position;
}


#shader fragment
#version 450 core

layout(location = 0) out vec4 a_Color;

in vec4 v_Color;
in vec2 v_TexCoords;
in flat float v_TexIndex;

uniform sampler2D u_Samplers[16];

void main()
{
	int index = int(v_TexIndex);
	a_Color = texture(u_Samplers[index], v_TexCoords) * v_Color;
}