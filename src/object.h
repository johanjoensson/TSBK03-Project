#ifndef OBJECT_H
#define OBJECT_H

#include "VectorUtils3.h"

class Object{
 protected:
  mat4 rot_mat;
  mat4 trans_mat;
public:
   
  mat4 matrix;
  vec3 position;
  
  
  void translate(float dx, float dy, float dz);
  void translate(vec3 dr);
  void place(vec3 pos);


  virtual  void update() =0;
  virtual  void rotate(char direction, float angle) =0;

  
  //Constructors
  Object();
};

#endif
