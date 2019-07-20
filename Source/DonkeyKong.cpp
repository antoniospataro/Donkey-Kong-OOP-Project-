#include "../Headers/DonkeyKong.h"
DonkeyKong::DonkeyKong(const int& x,const int& y):Entity(x,y),cont(0),petto(0),lancia(false){srand((unsigned)time(NULL));}
int DonkeyKong::getCont(){return cont;}
int DonkeyKong::increaseCont(){
    if(cont==30){
        bool lancia=true;
        cont=-1;
        petto=0;
    }
    cont++;
    if(cont==1)
        lancia=false;
    if(cont==10&& petto!=(MEDIUM-1)){
        cont=0;
        petto=rand() % MEDIUM;
    }
    return cont;
}
void DonkeyKong::Draw(){
    increaseCont();
    if(getCont()<=5){
        bip=al_load_bitmap("../Sprites/DK1.png");
        al_draw_bitmap(bip,getX(),getY(),0);
        al_destroy_bitmap(bip);
    }
    else if(getCont()>5&&getCont()<=10){
        bip=al_load_bitmap("../Sprites/DK2.png");
        al_draw_bitmap(bip,getX(),getY(),0);
        al_destroy_bitmap(bip);
    }
    else if(getCont()>10&&getCont()<=15){
        bip=al_load_bitmap("../Sprites/DK3.png");
        al_draw_bitmap(bip,getX(),getY(),0);
        al_destroy_bitmap(bip);
    }
    else if(getCont()>15&&getCont()<=20){
        bip=al_load_bitmap("../Sprites/DK4.png");
        al_draw_bitmap(bip,getX(),getY(),0);
        al_destroy_bitmap(bip);                            
    }
    else{
            bip=al_load_bitmap("../Sprites/DK5.png");
            al_draw_bitmap(bip,getX(),getY(),0);
            al_destroy_bitmap(bip);
    }
}      

