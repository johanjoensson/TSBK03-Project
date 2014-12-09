#version 150

in vec3 f_Normal;
in vec3 f_Position;
in vec2 f_TexCoord;

out vec4 out_Color;

uniform vec3 lightSourceColor;
uniform vec4 lightSourceDir;
uniform vec3 cam_pos;
uniform sampler2D objTex;


void main(void)
{
	float shade;
	//Ambient light
	out_Color = texture(objTex, f_TexCoord);
     	vec4 diffuse;
	vec4 specular;
     	/* Vector from surface to light source */
     	vec3 direction = f_Position - vec3(lightSourceDir); 

     	/* Diffuse shading */
     	shade = dot(normalize(f_Normal), normalize(-direction));
     	shade = clamp(shade, 0, 1);     
	diffuse = out_Color*vec4(shade*lightSourceColor, 1.0);

	/*Specular shading */
	vec3 r = 2*dot(normalize(-direction), normalize(f_Normal))*f_Normal + direction;
	shade = dot(normalize(cam_pos - f_Position), normalize(r));
	shade = pow(shade, 8);
	shade = clamp(shade, 0,1);
	specular = out_Color*vec4(shade*lightSourceColor, 1.0);
     	
	out_Color += diffuse;
	out_Color += specular;
}
