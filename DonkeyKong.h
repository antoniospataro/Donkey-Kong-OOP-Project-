#ifndef DONKEYKONG_H
#define DONKEYKONG_H
#include"Entity.h"
#include<ctime>
enum difficulty{HARD=1,MEDIUM=3,EASY=5};
class DonkeyKong: public Entity{
    private:
        int cont;
        int petto;
        ALLEGRO_BITMAP* bip;
        bool lancia;
    public:
        DonkeyKong(const int& x=0,const int& y=0):Entity(x,y),cont(0),petto(0),lancia(false){srand((unsigned)time(NULL));}
        int getCont(){return cont;}
        int increaseCont(){
            if(cont==30){
                bool lancia=true;
                cont=-1;
                petto=0;
            }
            cont++;
            if(cont==1)
                lancia=false;
            if(cont==12&& petto!=(EASY-1)){
                cont=0;
                petto=rand() % EASY;
            }
            return cont;
        }
        void Draw(){
            increaseCont();
            if(getCont()<=6){
                                bip=al_load_bitmap("Sprites/DK1.png");
                                al_draw_bitmap(bip,getX(),getY(),0);
                                al_destroy_bitmap(bip);
                        }
                        else if(getCont()>6&&getCont()<=12){
                                bip=al_load_bitmap("Sprites/DK2.png");
                                al_draw_bitmap(bip,getX(),getY(),0);
                                al_destroy_bitmap(bip);
                        }
                        else if(getCont()>12&&getCont()<=18){
                                bip=al_load_bitmap("Sprites/DK3.png");
                                al_draw_bitmap(bip,getX(),getY(),0);
                                al_destroy_bitmap(bip);
                        }
                        else if(getCont()>18&&getCont()<=24)
                        {
                                bip=al_load_bitmap("Sprites/DK4.png");
                                al_draw_bitmap(bip,getX(),getY(),0);
                                al_destroy_bitmap(bip);
                                
                        }
                        else{
                                bip=al_load_bitmap("Sprites/DK5.png");
                                al_draw_bitmap(bip,getX(),getY(),0);
                                al_destroy_bitmap(bip);
                                //draw barile;
                        }
        }      
};
#endif