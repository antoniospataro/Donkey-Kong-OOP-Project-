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
        bool up;
    public:
        Mario(const int& x=0,const int& y=0):Entity(x,y),cont(0),lancia(0),fall(false),right(false),left(false),down(false){srand((unsigned)time(NULL));}
        int getCont(){return cont;}

        void setFall(bool ok){fall=ok;}
        void setRight(bool ok){right=ok;}
        void setLeft(bool ok){left=ok;}
        void setDown(bool ok){down=ok;}
        void setUp(bool ok){up=ok;}
        bool getFall(){return fall;}
        bool getDown(){return down;}
        bool getRight(){return right;}
        bool getLeft(){return left;}
        bool getUp(){return up;}

        void moveLeft(){
            cont++;
            if(cont==1)
                bip=al_load_bitmap("Sprites/Walk1.png");
            else{
                bip=al_load_bitmap("Sprites/Walk2.png");cont=0;}
            al_draw_bitmap(bip,getX(),getY(),0);

        }

        void moveDown(){
            cont++;
            if(cont==1)
                bip=al_load_bitmap("Sprites/Climbing1.png");
            else{
                bip=al_load_bitmap("Sprites/Climbing2.png");cont=0;}
            al_draw_bitmap(bip,getX(),getY(),0);
        }
        void moveUp(){
            cont++;
            if(cont==1)
                bip=al_load_bitmap("Sprites/Climbing1.png");
            else{
                bip=al_load_bitmap("Sprites/Climbing2.png");cont=0;}
            al_draw_bitmap(bip,getX(),getY(),0);
        }
        void moveRight(){
            cont++;
            if(cont==1)
                bip=al_load_bitmap("Sprites/Walk1.png");
            else{
                bip=al_load_bitmap("Sprites/Walk2.png");cont=0;}
            al_draw_bitmap(bip,getX(),getY(),ALLEGRO_FLIP_HORIZONTAL);
        }
        void Draw(){
            bip=al_load_bitmap("Sprites/Walk0.png");
            al_draw_bitmap(bip,getX(),getY(),ALLEGRO_FLIP_HORIZONTAL);
            }
              
};
#endif 