#include"Entity.h"
#ifndef BARREL_H
#define BARREL_H

class Barrel:public Entity{
    private:
        int cont;
        bool scendi;
        bool destra;
        bool sinistra;
        public:
        Barrel(int x, int y):Entity(x,y),cont(0),scendi(false),destra(true),sinistra(false){}
        int barrelColor(){cont++;if(cont==2)cont=0;return cont;}
        void Draw(){
            if(!scendi)
            {
                cont++;
                if(sinistra)
                {
                    if(cont%2==0)
                    bip=al_load_bitmap("Sprites/Barrel.png");
                    al_draw_bitmap(bip,getX(),getY(),0);
                    al_destroy_bitmap(bip);
                }
            }
        }
};
#endif