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
        bool scale;
        bool reverse;
        bool jump;
    public:
        Mario(const int& x=0,const int& y=0):Entity(x,y),cont(0),lancia(0),scale(false),fall(false),right(false),left(false),down(false){srand((unsigned)time(NULL));}

        void setJump(bool ok){jump=ok;}
        void setReverse(bool ok){reverse=ok;}
        void setScale(int c){scale=c;}
        void setCont(int c){cont=c;}
        void setFall(bool ok){fall=ok;}
        void setRight(bool ok){right=ok;}
        void setLeft(bool ok){left=ok;}
        void setDown(bool ok){down=ok;}
        void setUp(bool ok){up=ok;}
        bool getJump(){return jump;}
        bool getReverse(){return reverse;}
        int getCont(){return cont;}
        bool getFall(){return fall;}
        bool getDown(){return down;}
        bool getRight(){return right;}
        bool getLeft(){return left;}
        bool getUp(){return up;}
        bool getScale(){return scale;}

        void Draw(bool ok){
            bip=al_load_bitmap("Sprites/Walk0.png");
            if(ok)
                al_draw_bitmap(bip,getX(),getY(),ALLEGRO_FLIP_HORIZONTAL);
            else
                al_draw_bitmap(bip,getX(),getY(),0);
            al_destroy_bitmap(bip);
            }
              
};
#endif 