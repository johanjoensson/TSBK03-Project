/*****************************************************************
 * World is the class handling all objects that the game includes
*****************************************************************/

#ifndef WORLD_H
#define WORLD_H

#include "object.h"

class World {
 protected:
  Object o;
 public:
  //Camera cam;
  void update();
  void draw(int);
  // void choseObject();
  // void moveObject();
  // void removeObject();
  // void addObject(int);
  World();
};

#endif
