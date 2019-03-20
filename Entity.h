class Entity{
    private:
        int x;
        int y;
       
    public:
        Entity(const int& a=0,const int& b=0):x(a),y(b){}
        int getX(){return x;}
        int getY(){return y;}
        void setX(const int& x){this->x=x;} 
        void setY(const int& y){this->y=y;}
        ~Entity(){}
};