#version 150 
//#extension GL_ARB_geometry_shader4 : enable
layout(triangles) in;
layout(triangle_strip, max_vertices=3) out;
in vec3 ex_Position[3];
in vec3 ex_Normal[3];
in vec2 ex_TexCoord[3];
out vec3 f_Normal;
out vec2 f_TexCoord;	     
out vec3 f_Position;
uniform vec3 lightSourceDir;
void main()
{
  for(int i = 0; i < gl_in.length(); i++)
    {
      // copy attributes
      gl_Position = gl_in[i].gl_Position;
      f_Normal = ex_Normal[i];
      f_TexCoord = ex_TexCoord[i];
      f_Position = ex_Position[i];
 
      // done with the vertex
      EmitVertex();
    }
  EndPrimitive();
}
