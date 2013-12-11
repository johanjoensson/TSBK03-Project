#include "body.h"

Body::Body()
{
    reflectivity = 1;
    scale = 1;
    scale_mat = S(scale, scale, scale);
}

Body::Body(const char *model)
{
  m = LoadModelPlus((char*)model);
  reflectivity = 1;
  scale = 1;
  scale_mat = S(scale, scale, scale);
}

Body::Body(const char *model, const char *tex)
{
  m = LoadModelPlus((char*)model);

  LoadTGATextureSimple((char*)tex ,&texture);
  printError("load textures");
 
  glActiveTexture(GL_TEXTURE0); // Activate ground texture
  glBindTexture(GL_TEXTURE_2D, texture); 

  reflectivity = 1;
  scale = 1;
  scale_mat = S(scale, scale, scale);
}

void Body::set_scale(float s)
{
  scale = s;
  scale_mat = S(scale,scale,scale);
  update();
}

float Body::get_scale()
{
  return scale;
}
void Body::draw(int program){
  glUniform1i(glGetUniformLocation(program, "objTex"), 0); 
  glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix"), 1, GL_TRUE, matrix.m);
  DrawModel(m, program, "in_Position", "in_Normal","in_TexCoord");
}

void Body::rotate(char direction, float angle)
{
  switch (direction) {
  case 'x':
    // Rotate around x
    rot_mat = Rx(angle) * rot_mat;
    break;
  case 'y':
    // Rotate around y
    rot_mat = rot_mat * Ry(angle) * rot_mat;
    break;
  case 'z':
    // Rotate around z
    rot_mat = Rz(angle) * rot_mat;
    break;
  }
  update();
}

void Body::update()
{
  matrix = trans_mat * rot_mat * scale_mat;
}
