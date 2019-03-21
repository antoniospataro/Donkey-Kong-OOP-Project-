#include"Entity.h"
#include<ctime>
#ifndef MARIO_H
#define MARIO_H
class Mario: public Entity{
    private:
        int cont;
        int petto;
        ALLEGRO_BITMAP* bip;
        bool lancia;
    public:
        Mario(const int& x=0,const int& y=0):Entity(x,y),cont(0),petto(0),lancia(false){srand((unsigned)time(NULL));}
        int getCont(){return cont;}
        int increaseCont(){
            if(cont==51){
                bool lancia=true;
                cont=-1;
                petto=0;
            }
            cont++;
            if(cont==1)
                lancia=false;
            if(cont==20&& petto!=(EASY-1)){
                cont=0;
                petto=rand() % EASY;
            }
            return cont;
        }
        void Draw(){
            bip=al_load_bitmap("Sprites/walk0.png");
            al_draw_bitmap(bip,getX(),getY(),0);
            al_destroy_bitmap(bip);
            //draw barile;
        }
              
};
#endif