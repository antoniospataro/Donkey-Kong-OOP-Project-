#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
using namespace std;

class Sounds
{
    private:
        ALLEGRO_SAMPLE* game;
        ALLEGRO_SAMPLE* death;
        ALLEGRO_SAMPLE* walking;
        ALLEGRO_SAMPLE* win;
        ALLEGRO_SAMPLE* jump;
        ALLEGRO_SAMPLE* winner;
        ALLEGRO_SAMPLE_INSTANCE* walkingInstance;
        ALLEGRO_SAMPLE_INSTANCE* jumpInstance;
       
    public:
        Sounds();

        void startGame();
        void playDeath();
        void playWin();
        void playWalking();
        void playJump();
        void stopSounds();
        void playWinner();
        ~Sounds();

};