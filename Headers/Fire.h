#ifndef FIRE_H
#define FIRE_H

#include "Entity.h"

class Fire : public Entity {
private:
  int cont;
  bool right;
  bool left;

public:
  Fire(const int &x, const int &y);
  void setRight(const bool &ok);
  void setLeft(const bool &ok);
  bool getLeft();
  bool getRight();
  void Draw();
};
#endif