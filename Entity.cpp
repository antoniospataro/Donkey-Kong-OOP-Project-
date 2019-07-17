#include "Entity.h"

Entity::Entity(const int& a=0,const int& b=0):x(a),y(b){}
int Entity:: getX(){return x;}
int Entity:: getY(){return y;}
void Entity:: setX(const int& x){this->x=x;} 
void Entity:: setY(const int& y){this->y=y;}
Entity::~Entity(){}