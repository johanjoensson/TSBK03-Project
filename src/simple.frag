#version 150

in vec3 ex_Normal;
in vec3 ex_Position;
in vec2 ex_TexCoord;

in vec3 out_cam;

out vec4 out_Color;

uniform vec3 lightSourceColor;
uniform vec4 lightSourceDir;
uniform vec3 cam_pos;
uniform sampler2D objTex;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;


void main(void)
{	
	float shade;
	vec4 light = viewMatrix*lightSourceDir;
	//Ambient light
	out_Color = texture(objTex, ex_TexCoord);
     	vec4 diffuse;
	vec4 specular;
     	// Vector from surface to light source 
     	vec3 direction = ex_Position - vec3(light); 

     	// Diffuse shading 
     	shade = dot(normalize(ex_Normal), normalize(-direction));
     	shade = clamp(shade, 0, 1);     
	diffuse = out_Color*vec4(shade*lightSourceColor, 1.0);

	//Specular shading 
	vec3 r = 2*dot(normalize(-direction), normalize(ex_Normal))*ex_Normal + direction;
	shade = dot(normalize(cam_pos - ex_Position), normalize(r));
	shade = pow(shade, 18);
	shade = clamp(shade, 0,1);
	specular = out_Color*vec4(shade*lightSourceColor, 1.0);
     	
	out_Color += diffuse;
	out_Color += specular;
	
  /*
	float shade = 0.7;
	
	vec3 s = normalize(vec3(lightSourceDir) - ex_Position);
	
	float sDOTn = dot(s, normalize(ex_Normal));
	clamp(sDOTn, 0, 1);
	
	float diffuse = sDOTn*shade;
	
	vec3 r = 2*normalize(ex_Normal)*sDOTn - s;
	vec3 v = normalize(cam_pos-ex_Position);

	int n = 7;
	float rDOTv = dot(normalize(r),v);
	float specular = pow(rDOTv,n)*shade;

	out_Color = vec4(shade/2 + diffuse+specular,shade/2 + diffuse+specular,shade/2 + diffuse+specular,1.0);
  */
}
