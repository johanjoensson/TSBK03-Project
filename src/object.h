#ifndef OBJECT_H
#define OBJECT_H

class Object{
 protected:
  mat4 rot_mat;
  mat4 trans_mat;
  mat4 scale_mat;
  float scale;
 public:
  Model *m;
  
  mat4 matrix;
  vec3 position = vec3(0,0,0);
  
  // Functions
  void set_scale(float);
  float get_scale(); 
  
  float reflectivity;
  GLuint texture;
  
  void rotate(char direction, float angle);
  void translate(float dx, float dy, float dz);
  void place(vec3 pos);
  void update();
  void draw(int);
  
  //Constructors
  Object();
  Object(const char*);
  Object(const char*, const char*);
};
	

#endif
