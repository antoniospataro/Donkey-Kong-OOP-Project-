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
        Mario(int x,int y);
        void setLife(int j);
        int getLife();
        void setJmp(int j);
        int getJmp();
        void setSpace(bool spa);
        void setJump(bool ok);
        void setReverse(bool ok);
        void setScale(int c);
        void setCont(int c);
        void setFall(bool ok);
        void setRight(bool ok);
        void setLeft(bool ok);
        void setDown(bool ok);
        void setUp(bool ok);
        void setHammer(bool ok);
        void setcontatoreHammer (int cont);
        bool getJump();
        bool getReverse();
        int getCont();
        bool getFall();
        bool getDown();
        bool getRight();
        bool getLeft();
        bool getUp();
        bool getScale();
        bool getSpace();
        bool getHammer();
        int getcontatoreHammer();
        void Draw(bool ok);
};

#endif 