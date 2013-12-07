#include "world.h"
#include <stdio.h>
GLfloat ground_arr[] = {        -1000, -1, 1000,
                        -1000, -1, -1000,
                        1000, -1, -1000,
                        1000, -1, -1000,
                        1000, -1, 1000,
                        -1000, -1, 1000 };
GLfloat gNormal[] = { 0.0f, 0.0f, 0.0f,
                 0.0f, 0.0f, 0.0f,
                 0.0f, 0.0f, 0.0f,
                 0.0f, 0.0f, 0.0f,
                 0.0f, 0.0f, 0.0f,
                 0.0f, 0.0f, 0.0f };

GLfloat ground_tex_coord[6][2] = {        {1.0, 0.0},
                                        {0.0, 0.0},
                                        {0.0, 1.0},
                                        {0.0, 1.0},
                                        {1.0, 1.0},
                                        {1.0, 0.0} };
GLuint ground_tex;
unsigned int groundVertexArrayObjID;
unsigned int gNormalArrayObjID;

World::World(){
  o = Body("src/obj/bunnyplus.obj", "src/obj/grass.tga");
  cam = Camera();
  ground = Body("src/obj/untitled.obj");
  ground.set_scale(1000);
}

void World::draw(int program){
    cam.draw(program);
    ground.draw(program);
    
    o.draw(program);
  // update();
} 

void World::update(){

//  o.translate( 1,  1, 1);

}
