#ifndef DONKEYKONG_H
#define DONKEYKONG_H

#include"Entity.h"
#include<ctime>
#include<iostream>

enum difficulty{HARD=1,MEDIUM=3,EASY=5};
class DonkeyKong: public Entity{
    private:
        int cont;
        int petto;
        ALLEGRO_BITMAP* bip;
        bool lancia;
    public:
        DonkeyKong(const int& x,const int& y);
        int getCont();
        int increaseCont();
        void Draw();
};
#endif
