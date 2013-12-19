#version 150

in vec3 ex_Normal;
in vec3 ex_Position;
in vec2 ex_TexCoord;

out vec4 out_Color;

uniform vec3 lightSourceColor;
uniform vec3 lightSourceDir;
uniform vec3 cam_pos;
uniform sampler2D objTex;


void main(void)
{
	float shade;
	//Ambient light
	out_Color=vec4(0.5,0.5,0.5,1.0);
	vec4 tex = texture(objTex, ex_TexCoord);
     	vec4 diffuse = vec4(0,0,0,0);
	vec4 specular = vec4(0,0,0,0);
     	/* Vector from surface to light source */
     	vec3 direction = ex_Position - lightSourceDir; 

     	/* Diffuse shading */
     	shade = dot(normalize(ex_Normal), normalize(-direction));
     	shade = clamp(shade, 0, 1);     
	diffuse += out_Color*vec4(shade*lightSourceColor, 1.0);

	/*Specular shading */
	vec3 r = 2*dot(normalize(-direction), normalize(ex_Normal))*ex_Normal + direction;
	shade = dot(normalize(cam_pos - ex_Position), normalize(r));
	shade = clamp(shade, 0,1);
	shade = pow(shade, 10);
	specular += vec4(shade*lightSourceColor, 1.0);
     	
	out_Color = tex;
	out_Color += diffuse;
	out_Color += specular;
}
