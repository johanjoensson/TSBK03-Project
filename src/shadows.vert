#version 150

in  vec3  in_Position;

in vec3 in_Normal;
in vec2 in_TexCoord;

uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

void main(void)
{  
	
	gl_Position = viewMatrix*modelMatrix*vec4(in_Position,1.0);
	//For use in Geom-shader

	vec3 normals = in_Normal;
	vec2 texcoords = in_TexCoord;
}
