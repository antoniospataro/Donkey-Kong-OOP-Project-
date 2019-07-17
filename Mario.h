#include"Entity.h"
#include<ctime>
#include<iostream>
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
        bool space;
        bool jump;
        bool hammer;
        int jmp;
        int contatoreHammer;
        int life;
    public:
        Mario(int x,int y):Entity(x,y),life(4),cont(0),lancia(0),scale(false),fall(false),right(false),left(false),down(false),hammer(false){
        srand((unsigned)time(NULL));}

        void setLife(int j){life=j;}
        int getLife(){return life;}
        void setJmp(int j){jmp=j;}
        int getJmp(){return jmp;}
        void setSpace(bool spa){space=spa;}
        void setJump(bool ok){jump=ok;}
        void setReverse(bool ok){reverse=ok;}
        void setScale(int c){scale=c;}
        void setCont(int c){cont=c;}
        void setFall(bool ok){fall=ok;}
        void setRight(bool ok){right=ok;}
        void setLeft(bool ok){left=ok;}
        void setDown(bool ok){down=ok;}
        void setUp(bool ok){up=ok;}
        void setHammer(bool ok){hammer=ok;}
        void setcontatoreHammer (int cont) {contatoreHammer = cont;}
        bool getJump(){return jump;}
        bool getReverse(){return reverse;}
        int getCont(){return cont;}
        bool getFall(){return fall;}
        bool getDown(){return down;}
        bool getRight(){return right;}
        bool getLeft(){return left;}
        bool getUp(){return up;}
        bool getScale(){return scale;}
        bool getSpace(){return space;}
        bool getHammer() {return hammer;}
        int getcontatoreHammer() {return contatoreHammer;}



        void Draw(bool ok){

            if (!hammer){
            bip=al_load_bitmap("Sprites/Walk0.png");
            if(ok)
                al_draw_bitmap(bip,getX(),getY(),ALLEGRO_FLIP_HORIZONTAL);
            else {
                al_draw_bitmap(bip,getX(),getY(),0);
                al_destroy_bitmap(bip);
            }
        }
        else{
            if (cont == 0){
                cont = 1;
                bip = al_load_bitmap("Sprites/Hammer1.png");
                if(ok)
                    al_draw_bitmap(bip,getX(),getY()-8,ALLEGRO_FLIP_HORIZONTAL);
                else 
                    al_draw_bitmap(bip,getX()+16,getY()-8,0);
                al_destroy_bitmap(bip);
            }
            else {
                cont = 0;
                bip = al_load_bitmap("Sprites/Hammer2.png");
                if(ok)
                    al_draw_bitmap(bip,getX(),getY(),ALLEGRO_FLIP_HORIZONTAL); // destra
                else 
                    al_draw_bitmap(bip,getX(),getY(),0); // sinistra
                al_destroy_bitmap(bip);
        }

        }
    }
}
;

#endif 