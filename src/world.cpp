#include "world.h"
#include <stdio.h>
#include "math.h"


World::World()
{
  o = Body("src/obj/bunnyplus.obj", "src/obj/grass.tga");
  p = Body("src/obj/bunnyplus.obj", "src/obj/SkyBox512.tga");
  o.rotate('y', 3.14/2);
  o.set_scale(2);
  p.translate(0.0,1.0,0.0);
  o.place(vec3(0.5,-1.0,0.0));


  cam = Camera();
  ground = Body("src/obj/ground.obj", "src/obj/grass.tga");
  ground.place(vec3(0,-1.0,0));
  ground.set_scale(100);
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


}
