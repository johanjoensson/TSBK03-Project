#version 150

// in vec3 f_Normal;
// in vec3 f_Position;
// in vec2 f_TexCoord;
in vec3 ex_Normal;
in vec3 ex_Position;
in vec2 ex_TexCoord;
out vec4 out_Color;

uniform vec3 lightSourceColor;
uniform vec4 lightSourceDir;
uniform vec3 cam_pos;
uniform sampler2D objTex;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;


void main(void)
{
	float shade;
	vec4 light = viewMatrix*lightSourceDir;
	//Ambient light
	out_Color = 0.2*texture(objTex, ex_TexCoord);
}
