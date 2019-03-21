#include"Entity.h"
#include<ctime>
#ifndef MARIO_H
#define MARIO_H
class Mario: public Entity{
    private:
        int cont;
        ALLEGRO_BITMAP* bip;
        bool lancia;
        bool fall;
        bool right;
        bool left;
        bool down;
        bool scale;
    public:
        Mario(const int& x=0,const int& y=0):Entity(x,y),cont(0),lancia(0),fall(false),right(false),left(false),down(false){srand((unsigned)time(NULL));}
        int getCont(){return cont;}
        void moveLeft(bool& ok){
            if(!ok)
                return;
        }
        void moveDown(bool& ok){
            if(!ok)
                return;
        }
        void moveUp(bool& ok){
            if(!ok)
                return;
        }
        void moveRight(bool& ok){
            if(!ok)
                return;
        }
        void Draw(int& pos_x,int&pos_y){
            
            bip=al_load_bitmap("Sprites/walk0.png");
            al_draw_bitmap(bip,getX(),getY(),ALLEGRO_FLIP_HORIZONTAL);
            //al_draw_rotated_bitmap(bip,0,0,getX(),getY(),270,0);
            al_destroy_bitmap(bip);
            //draw barile;
        }
              
};
#endif 