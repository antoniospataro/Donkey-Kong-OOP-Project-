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
        Barrel(int x,int y):Entity(x,y),cont(0),down(false),right(true),left(false){}
        int barrelColor(){cont++;if(cont==2)cont=0;return cont;}
        void setRight(bool ok){right=ok;}
        void setFall(bool ok){fall=ok;}
        void setLeft(bool ok){left=ok;}
        void setDown(bool ok){down=ok;}
        bool getLeft(){return left;}
        bool getRight(){return right;}
        bool getDown(){return down;}
        bool getFall(){return fall;}
        void Draw(){
            if(down==false&&fall==false)
            {
                if(left==true){ 
                    setX(getX()-8);
                    if(cont==0)
                        bip=al_load_bitmap("Sprites/Barrel1.png");
                    else if(cont==1)
                        bip=al_load_bitmap("Sprites/Barrel2.png");
                    else if(cont==2)
                        bip=al_load_bitmap("Sprites/Barrel3.png");
                    else
                        bip=al_load_bitmap("Sprites/Barrel4.png");
                    
                    al_draw_bitmap(bip,getX(),getY(),0);
                    al_destroy_bitmap(bip);
                }
                else if(right==true){
                    setX(getX()+8);
                    if(cont==0)
                        bip=al_load_bitmap("Sprites/Barrel1.png");
                    else if(cont==1)
                        bip=al_load_bitmap("Sprites/Barrel2.png");
                    else if(cont==2)
                        bip=al_load_bitmap("Sprites/Barrel3.png");
                    else
                        bip=al_load_bitmap("Sprites/Barrel4.png");
                    al_draw_bitmap(bip,getX(),getY(),0);
                    al_destroy_bitmap(bip);
                }
            }    
            else{
                setY(getY()+8);
                if(cont==0||cont==2)
                    bip=al_load_bitmap("Sprites/Barrel5.png");
                else
                    bip=al_load_bitmap("Sprites/Barrel6.png");
                al_draw_bitmap(bip,getX(),getY(),0);
                al_destroy_bitmap(bip);
            }
            cont++;
            if(cont==4)
                cont=0;
        }

    Barrel operator= (Barrel& b){
        if (this != &b){
            this->setX(b.getX());
            this->setY(b.getY());
            this->cont = b.cont;
            this->right = b.right;
            this->fall = b.fall;
            this->left = b.left;
            this->down = b.down;
        }
        return *this;
    }
};
#endif