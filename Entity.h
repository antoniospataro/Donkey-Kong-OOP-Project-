#include<allegro5/allegro5.h>
#ifndef ENTITY_H
#define ENTITY_H
class Entity{
    private:
        int x;
        int y;
    protected:
        ALLEGRO_BITMAP* bip;
       
    public:
        Entity(const int& a,const int& b);
        int getX();
        int getY();
        void setX(const int& x); 
        void setY(const int& y);
        virtual void Draw(){}
        ~Entity();
};
#endif