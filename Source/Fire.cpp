#include "../Headers/Fire.h"

Fire::Fire(const int &x, const int &y)
    : Entity(x, y), cont(0), right(true), left(false) {}

bool Fire::getLeft() { return left; }

bool Fire::getRight() { return right; }

void Fire::setLeft(const bool &ok) { left = ok; }

void Fire::setRight(const bool &ok) { right = ok; }

void Fire::Draw() {
  if (left == true) {
    setX(getX() - 8);
    if (cont == 0)
      bip = al_load_bitmap("../Sprites/fiamma1.png");
    else if (cont == 1)
      bip = al_load_bitmap("../Sprites/fiamma2.png");
    else if (cont == 2)
      bip = al_load_bitmap("../Sprites/fiamma3.png");
    else
      bip = al_load_bitmap("../Sprites/fiamma4.png");

    al_draw_bitmap(bip, getX(), getY(), ALLEGRO_FLIP_HORIZONTAL);
    al_destroy_bitmap(bip);
  } else if (right == true) {
    setX(getX() + 8);
    if (cont == 0)
      bip = al_load_bitmap("../Sprites/fiamma1.png");
    else if (cont == 1)
      bip = al_load_bitmap("../Sprites/fiamma2.png");
    else if (cont == 2)
      bip = al_load_bitmap("../Sprites/fiamma3.png");
    else
      bip = al_load_bitmap("../Sprites/fiamma4.png");
    al_draw_bitmap(bip, getX(), getY(), 0);
    al_destroy_bitmap(bip);
  }
  cont++;
  if (cont == 4)
    cont = 0;
}