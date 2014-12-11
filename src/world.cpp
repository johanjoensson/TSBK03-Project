#include "world.h"
#include <stdio.h>

World::World()
{
  o = Body("src/obj/bunnyplus.obj", "src/obj/grass.tga");
  p = Body("src/obj/bunnyplus.obj", "src/obj/SkyBox512.tga");
  o.rotate('y', 3.14/2);
  o.set_scale(0.5);
  p.translate(0.0,1.0,0.0);
  o.place(vec3(0.5,0.0,0.0));


  cam = Camera();
  ground = Body("src/obj/untitled.obj", "src/obj/grass.tga");
  ground.place(vec3(0,0.0,0));
  ground.set_scale(10);
}

void World::draw(int program)
{
   cam.draw(program);

   ground.draw(program);
    
   o.draw(program);
   p.draw(program);
} 

void World::update()
{

//  o.translate( 1,  1, 1);

}
