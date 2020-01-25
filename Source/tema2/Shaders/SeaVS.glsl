#version 400

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_color;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float Time;

out vec3 frag_normal;
out vec3 frag_color;
out vec2 tex_coord;

void main()
{
	frag_normal = v_normal;
	frag_color = v_color;
	tex_coord = v_texture_coord;
	vec4 v=vec4(v_position,1.0);
	if(v_color== vec3(0.36f, 0.67f, 0.93f))
	{
		v.z+=0.01f*sin(Time);
		v.y+=0.01f*cos(Time);
	}
	if(v_color== vec3(0.16f, 0.17f, 0.93f) || v_color== vec3(0.26f, 0.57f, 0.93f))
	{
		v.z+=0.005f*cos(Time);
		v.y+=0.005f*sin(Time);
	}
	if(v_color== vec3(0.27f, 0.4f, 0.93f) || v_color== vec3(0.16f, 0.47f, 0.93f))
	{
		v.z+=0.015f*sin(Time);
		v.y+=0.015f*cos(Time);
	}
	if(v_color== vec3(0.05f, 0.5f, 0.93f) || v_color== vec3(0.06f, 0.37f, 0.93f))
	{
		v.z+=0.02f*cos(Time);
		v.y+=0.02f*sin(Time);
	}		
	gl_Position = Projection * View * Model * v;
}
