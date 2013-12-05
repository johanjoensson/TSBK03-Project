#include <GL/gl.h>
#include "MicroGlut.h"
#include "VectorUtils3.h"
#include "loadobj.h"
#include "GL_utilities.h"
#include "LoadTGA.h"
#include "zpr.h"

#include "world.h"

World::World(){
  o = Object("src/obj/bunnyplus.obj", "src/obj/grass.tga");

}

void World::draw(int program){
  o.draw(program);
  // update();
} 

void World::update(){

  o.translate( 1,  1, 1);

}
