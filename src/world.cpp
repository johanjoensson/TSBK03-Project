#include "world.h"
#include <stdio.h>

World::World()
{
  o = Body("src/obj/bunnyplus.obj", "src/obj/grass.tga");
  o.rotate('y', 3.14/2);
  cam = Camera();
  ground = Body("src/obj/bunnyplus.obj", "src/obj/grass.tga");
  ground.set_scale(0.5);
  ground.update();
}

void World::draw(int program)
{
    cam.draw(program);
    ground.draw(program);
    
    o.draw(program);
  // update();
} 

void World::update()
{

//  o.translate( 1,  1, 1);

}
