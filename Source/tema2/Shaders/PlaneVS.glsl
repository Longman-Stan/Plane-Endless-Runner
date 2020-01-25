#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_color;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform vec3 light_position;
uniform vec3 eye_position;
uniform float material_kd;
uniform float material_ks;
uniform float material_shininess;

out vec3 frag_normal;
out vec3 frag_color;
out vec2 tex_coord;

void main()
{

	vec3 world_pos = (Model * vec4(v_position,1)).xyz;
	vec3 world_normal = normalize(mat3(Model)*v_position);

	vec3 L = normalize( light_position - world_pos);
	vec3 V = normalize( eye_position - world_pos);
	vec3 H = normalize(L+V);

	float ambient_light = 0.60f;

	float diffuse_light = 100*material_kd* max( 0, dot(world_normal,L));

	float primeste_lumina;
	if( dot(v_position,L)>0)
		primeste_lumina = 1;
	else
		primeste_lumina = 0;

	float specular_light = material_ks*primeste_lumina*pow( max( dot(world_normal,H),0),material_shininess);

	float d = distance(world_pos,light_position);
	float atenuation = 1/(d*d);

	float light = ambient_light+atenuation*(diffuse_light + specular_light);

	frag_normal = v_normal;
	frag_color = v_color*light;
	tex_coord = v_texture_coord;
	gl_Position = Projection * View * Model * vec4(v_position, 1.0);
}
