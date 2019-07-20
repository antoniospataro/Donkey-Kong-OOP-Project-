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
        Mario(const int& x,const int& y);
        void setLife(const int& j);
        int getLife();
        void setJmp(const int& j);
        int getJmp();
        void setSpace(const bool& spa);
        void setJump(const bool& ok);
        void setReverse(const bool& ok);
        void setScale(const int& c);
        void setCont(const int& c);
        void setFall(const bool& ok);
        void setRight(const bool& ok);
        void setLeft(const bool& ok);
        void setDown(const bool& ok);
        void setUp(const bool& ok);
        void setHammer(const bool& ok);
        void setcontatoreHammer (const int& cont);
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
        void Draw(const bool& ok);
};

#endif 