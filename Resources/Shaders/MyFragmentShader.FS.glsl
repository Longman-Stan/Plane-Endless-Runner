#version 330

in vec3 frag_color;

layout(location = 0) out vec4 out_color;

void main()
{
	if(frag_color==vec3(0.f, 0.75f, 1.f))
		out_color = vec4(frag_color,0.2);
	else out_color = vec4(frag_color,1);
}