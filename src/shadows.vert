#version 150

in  vec3  in_Position;

uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

void main(void)
{  
	
	gl_Position = viewMatrix*modelMatrix*vec4(in_Position,1.0);
	//For use in Geom-shader

}
