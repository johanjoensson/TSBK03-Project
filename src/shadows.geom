#version 150 
layout(triangles_adjacency) in;
layout(triangle_strip, max_vertices=18) out;


uniform vec4 lightSourceDir;
uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;

void main()
{

  vec4 light = viewMatrix*lightSourceDir;
  vec3 ns[3];
  vec3 d[3];
  vec4 or_pos[3]; // Triangle oriented toward light source  
  vec4 v[4]; //Temporary vertices
  or_pos[0]= gl_in[0].gl_Position;  
  or_pos[1]= gl_in[2].gl_Position;  
  or_pos[2]= gl_in[4].gl_Position; 
 
  // Compute normal at each vertex.
  ns[0] = cross(
		 vec3(gl_in[2].gl_Position - gl_in[0].gl_Position),
		 vec3(gl_in[4].gl_Position - gl_in[0].gl_Position));
  ns[1] = cross(
		vec3(gl_in[4].gl_Position - gl_in[2].gl_Position),
		vec3(gl_in[0].gl_Position - gl_in[2].gl_Position) );
  ns[2] = cross(
		vec3(gl_in[0].gl_Position - gl_in[4].gl_Position),
		vec3(gl_in[2].gl_Position - gl_in[4].gl_Position) );
  
  d[0] = light.xyz-light.w*vec3(gl_in[0].gl_Position);
  d[1] = light.xyz-light.w*vec3(gl_in[2].gl_Position);
  d[2] = light.xyz-light.w*vec3(gl_in[4].gl_Position);
  
  bool faces_light = true;  
  if ( !(dot(ns[0],d[0])>0 || dot(ns[1],d[1])>0 ||  
	 dot(ns[2],d[2])>0) ) {   
    // Flip vertex winding order in or_pos.  
    or_pos[1] = gl_in[4].gl_Position;  
    or_pos[2] = gl_in[2].gl_Position;  
    faces_light = false;  
  }  
  for ( int i=0; i<3; i++ ) {
    // Compute indices of neighbor triangle.
    int v0 = i*2;
    int nb = (i*2+1);
    int v1 = (i*2+2) % 6;
    // Compute normals at vertices, the *exact*
    // same way as done above!
    ns[0] = cross(
  		  vec3(gl_in[nb].gl_Position-gl_in[v0].gl_Position),
  		  vec3(gl_in[v1].gl_Position-gl_in[v0].gl_Position));
    ns[1] = cross(
  		  vec3(gl_in[v1].gl_Position-gl_in[nb].gl_Position),
  		  vec3(gl_in[v0].gl_Position-gl_in[nb].gl_Position));
    ns[2] = cross(
  		  vec3(gl_in[v0].gl_Position-gl_in[v1].gl_Position),
  		  vec3(gl_in[nb].gl_Position-gl_in[v1].gl_Position));

    // Compute direction to light, again as above.
    d[0] =light.xyz-light.w*vec3(gl_in[v0].gl_Position);
    d[1] =light.xyz-light.w*vec3(gl_in[nb].gl_Position);
    d[2] =light.xyz-light.w*vec3(gl_in[v1].gl_Position);
     // Extrude the edge if it does not have a   
    // neighbor, or if it's a possible silhouette.   
    if ( gl_in[nb].gl_Position.w < 1e-3 ||
  	 ( faces_light != (dot(ns[0],d[0])>0 ||
  			   dot(ns[1],d[1])>0 ||
  			   dot(ns[2],d[2])>0) ))
      {
   	// Make sure sides are oriented correctly.   
  	int i0 = faces_light ? v0 : v1;
  	int i1 = faces_light ? v1 : v0;
  	v[0] = gl_in[i0].gl_Position;
  	v[1] = vec4(light.w*vec3(gl_in[i0].gl_Position) - light.xyz, 0);
  	v[2] = gl_in[i1].gl_Position;
  	v[3] = vec4(light.w*vec3(gl_in[i1].gl_Position) -
  light.xyz, 0);
  	// Emit a quad as a triangle strip.
  	gl_Position = projectionMatrix*v[0];
  	EmitVertex();
  	gl_Position = projectionMatrix*v[1];
  	EmitVertex();
  	gl_Position = projectionMatrix*v[2];
  	EmitVertex();
  	gl_Position = projectionMatrix*v[3];
  	EmitVertex(); EndPrimitive();
      }
  }

}
