#version 150 
layout(triangles_adjacency) in;
layout(triangle_strip, max_vertices=3) out;
in vec3 ex_Position[];
in vec3 ex_Normal[];
in vec2 ex_TexCoord[];
out vec3 f_Normal;
out vec2 f_TexCoord;	     
out vec3 f_Position;

void main()
{
   //For pass through
   for(int i = 0; i < gl_in.length(); i += 2)
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
