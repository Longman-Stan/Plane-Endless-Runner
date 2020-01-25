#version 330

in vec3 frag_color;

layout(location = 0) out vec4 out_color;

void main()
{
	out_color = vec4(frag_color,1);
	if(frag_color[0]<0.1f && frag_color[1]>0.72f && frag_color[1]<0.77f && frag_color[2]>0.98f)
		out_color.a=0.1;

}