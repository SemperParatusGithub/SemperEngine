#shader vertex
#version 450

// Simple OpenGL Raster Shader
// Credits to: https://github.com/ceranco/OpenGL-Grid

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoords;

uniform mat4 u_ProjectionView;
uniform mat4 u_Transform;

out vec2 v_TexCoords;

void main()
{
	v_TexCoords = a_TexCoords;
	gl_Position = u_ProjectionView * u_Transform * vec4(a_Position, 1.0f);
}


#shader fragment
#version 450

in vec2 v_TexCoords;
layout(location = 0) out vec4 o_Color;

uniform vec3 u_GridColor;
uniform float u_Segments;

const float PI = 3.1415926535897932384626433832795;

vec2 convert_to_cell_coords(vec2 coord, vec2 grid);

float lineWidth = 0.05 / u_Segments;
vec2 cellSize = vec2(2) / vec2(u_Segments);

void main()
{
	vec2 cellCoord = convert_to_cell_coords(v_TexCoords, cellSize);
	vec2 cutoff = convert_to_cell_coords(vec2(1.0 - lineWidth), cellSize);

	vec2 alpha = step(cutoff, cellCoord);
	if (max(alpha.x, alpha.y) == 0.0)
		discard;

	o_Color = vec4(u_GridColor, 1.0);
}

vec2 convert_to_cell_coords(vec2 coord, vec2 cellSize)
{
	return cos(((2 * PI) / cellSize) * coord);
}