#include"Entity.h"

class Barrel:public Entity{
    private:
        int cont;
        Barrel(int x, int y):Entity(x,y),cont(0){}
        int barrelColor(){cont++;if(cont==2)cont=0;return cont;}
};