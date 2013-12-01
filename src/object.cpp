#include "MicroGlut.h"
#include "VectorUtils3.h"
#include "loadobj.h"
#include "LoadTGA.h"
#include "GL_utilities.h"
#include "zpr.h"
#include <GL/gl.h>
#include "object.h"


Object::Object(){
reflectivity = 1;
 scale = 1;
 matrix = IdentityMatrix();
 scale_mat = S(scale, scale, scale);
 rot_mat = IdentityMatrix();
 trans_mat = IdentityMatrix();
}

Object::Object(const char *model)
{
  m = LoadModelPlus((char*)model);
  reflectivity = 1;
  scale = 1;
  matrix = IdentityMatrix();
  scale_mat = S(scale, scale, scale);
  rot_mat = IdentityMatrix();
  trans_mat = IdentityMatrix();
}

Object::Object(const char *model, const char *tex)
{
  m = LoadModelPlus((char*)model);

  LoadTGATextureSimple((char*)tex ,&texture);
  printError("load textures");
 
  glActiveTexture(GL_TEXTURE0); // Activate ground texture
  glBindTexture(GL_TEXTURE_2D, texture); 

  reflectivity = 1;
  scale = 1;
  matrix = IdentityMatrix();
  scale_mat = S(scale, scale, scale);
  rot_mat = IdentityMatrix();
  trans_mat = IdentityMatrix();
}


////////////////////////////////////////////////////
// FUNCTIONS////////////////////////////////////////
////////////////////////////////////////////////////

void Object::set_scale(float s)
{
  scale = s;
  scale_mat = S(scale,scale,scale);
}

float Object::get_scale()
{
  return scale;
}

void Object::draw(int program){
  glUniform1i(glGetUniformLocation(program, "objTex"), 0); 
  DrawModel(m, program, "in_Position", "in_Normal","in_TexCoord");
}

void Object::rotate(char direction, float angle)
{
  switch (direction) {
  case 'x':
    // Rotate around x
    rot_mat = Rx(angle) * rot_mat;
    update();
    break;
  case 'y':
    // Rotate around y
    rot_mat = rot_mat * Ry(angle) * rot_mat;
    update();
    break;
  case 'z':
    // Rotate around z
    rot_mat = Rz(angle) * rot_mat;
    update();
    break;
  }
}

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

void Object::update()
{
  matrix = trans_mat * rot_mat * scale_mat;
}
