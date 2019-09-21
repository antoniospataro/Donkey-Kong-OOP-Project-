#ifndef BARREL_H
#define BARREL_H

#include "Entity.h"
#include <iostream>

class Barrel : public Entity {
private:
  int cont;
  bool down;
  bool right;
  bool left;
  bool fall;

public:
  Barrel(const int &x, const int &y);
  int barrelColor();
  void setRight(const bool &ok);
  void setFall(const bool &ok);
  void setLeft(const bool &ok);
  void setDown(const bool &ok);
  bool getLeft();
  bool getRight();
  bool getDown();
  bool getFall();
  void Draw();
  Barrel operator=(Barrel &b);
};
#endif