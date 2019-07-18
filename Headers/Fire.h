#ifndef FIRE_H
#define FIRE_H

#include"Entity.h"


class Fire:public Entity{
    private:
        int cont;
        bool right;
        bool left;
    public:
        Fire(int x,int y);
        void setRight(bool ok);
        void setLeft(bool ok);
        bool getLeft();
        bool getRight();
        void Draw();
};
#endif