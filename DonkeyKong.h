#include"Entity.h"
#include<ctime>
enum difficulty{HARD=1,MEDIUM=3,EASY=5};
class DonkeyKong: public Entity{
    private:
        int cont;
        int petto;
    public:
        DonkeyKong(const int& x=0,const int& y=0):Entity(x,y),cont(0),petto(0){srand((unsigned)time(NULL));}
        int getCont(){return cont;}
        int increaseCont(){
            if(cont==51){
                cont=-1;
                petto=0;
            }
            cont++;
            if(cont==20&& petto!=(EASY-1)){
                cont=0;
                petto=rand() % EASY;
            }
            return cont;
        }
        
};