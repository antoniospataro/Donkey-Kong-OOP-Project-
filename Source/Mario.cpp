#include "../Headers/Mario.h"

Mario::Mario(const int& x,const int& y):Entity(x,y),life(10),cont(0),lancia(0),scale(false),fall(false),right(false),left(false),down(false),hammer(false){srand((unsigned)time(NULL));}

void Mario::setLife(const int& j){life=j;}
void Mario::setJmp(const int& j){jmp=j;}
void Mario::setSpace(const bool& spa){space=spa;}
void Mario::setJump(const bool& ok){jump=ok;}
void Mario::setReverse(const bool& ok){reverse=ok;}
void Mario::setScale(const int& c){scale=c;}
void Mario::setCont(const int& c){cont=c;}
void Mario::setFall(const bool& ok){fall=ok;}
void Mario::setRight(const bool& ok){right=ok;}
void Mario::setLeft(const bool& ok){left=ok;}
void Mario::setDown(const bool& ok){down=ok;}
void Mario::setUp(const bool& ok){up=ok;}
void Mario::setHammer(const bool& ok){hammer=ok;}
void Mario::setcontatoreHammer (const int& cont) {contatoreHammer = cont;}
bool Mario::getJump(){return jump;}
bool Mario::getReverse(){return reverse;}
bool Mario::getFall(){return fall;}
bool Mario::getDown(){return down;}
bool Mario::getRight(){return right;}
bool Mario::getLeft(){return left;}
bool Mario::getUp(){return up;}
bool Mario::getScale(){return scale;}
bool Mario::getSpace(){return space;}
bool Mario::getHammer() {return hammer;}
int Mario::getcontatoreHammer() {return contatoreHammer;}
int Mario::getCont(){return cont;}
int Mario::getLife(){return life;}
int Mario::getJmp(){return jmp;}
void Mario::Draw(const bool& ok){
    if (!hammer){
        bip=al_load_bitmap("../Sprites/Walk0.png");
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
            bip = al_load_bitmap("../Sprites/Hammer1.png");
            if(ok)
                al_draw_bitmap(bip,getX(),getY()-8,ALLEGRO_FLIP_HORIZONTAL);
            else 
                al_draw_bitmap(bip,getX()+16,getY()-8,0);
            al_destroy_bitmap(bip);
        }
        else {
            cont = 0;
            bip = al_load_bitmap("../Sprites/Hammer2.png");
            if(ok)
                al_draw_bitmap(bip,getX(),getY(),ALLEGRO_FLIP_HORIZONTAL); // destra
            else 
                al_draw_bitmap(bip,getX(),getY(),0); // sinistra
            al_destroy_bitmap(bip);
        }
    }
}