#ifndef BARREL_H
#define BARREL_H

#include"Entity.h"
#include<iostream>


class Barrel:public Entity{
    private:
        int cont;
        bool down;
        bool right;
        bool left;
        bool fall;
    public:
        Barrel(int x,int y);
        int barrelColor();
        void setRight(bool ok);
        void setFall(bool ok);
        void setLeft(bool ok);
        void setDown(bool ok);
        bool getLeft();
        bool getRight();
        bool getDown();
        bool getFall();
        void Draw();
        Barrel operator= (Barrel& b);
};
#endif