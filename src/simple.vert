#version 150

in  vec3  in_Position;
in  vec3  in_Normal;
in  vec2  in_TexCoord;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;


out vec3 ex_Normal;
out vec3 ex_Position;
out vec2 ex_TexCoord;
out vec3 out_cam;
void main(void)
{   
//	gl_PositionIn = in_Position;
	ex_TexCoord = in_TexCoord;
	ex_Normal =  mat3(modelMatrix)*in_Normal;
	out_cam = vec3(viewMatrix*vec4(in_Position,1));
	
	gl_Position = projectionMatrix*viewMatrix*modelMatrix*vec4(in_Position, 1.0); 
//	gl_Position = viewMatrix*modelMatrix*vec4(in_Position,1.0); //For use in Geom-shader
	ex_Position = vec3(viewMatrix*modelMatrix*vec4(in_Position, 1.0)); 
}
