#include "MicroGlut.h"
#include "VectorUtils3.h"
//#include "loadobj.h"
#include "LoadTGA.h"
#include "GL_utilities.h"
#include "zpr.h"
#include <GL/gl.h>
#include "object.h"


Object::Object(){
 matrix = IdentityMatrix();
 rot_mat = IdentityMatrix();
 trans_mat = IdentityMatrix();
 position = vec3(0,0,0);
}




////////////////////////////////////////////////////
// FUNCTIONS////////////////////////////////////////
////////////////////////////////////////////////////

void Object::place(vec3 pos)
{
  trans_mat = T(pos.x, pos.y, pos.z);
  update();
}

void Object::translate(float dx, float dy, float dz)
{
  trans_mat = T(dx, dy, dz)* trans_mat;
  update();
}

void Object::translate(vec3 dr)
{
  trans_mat = T(dr.x, dr.y, dr.z)* trans_mat;
  update();
}
