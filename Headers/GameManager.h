#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "Graphic.h"
#include <algorithm>
#include "Mario.h"
#include "Sounds.h"

using namespace std;
extern int x;
extern int y;
extern int pixel;

class GameManager {

    private:
        bool pressStart = true;
        bool menu = true;
        bool Exit = false;
        bool redraw = true;
        bool keys[7] = {false, false, false, false, false, false, false};
        bool backGroundMusic = true;
        bool walkSound = false;
        bool change = false;
        bool mute = false;
        bool move = false;
        int FPS = 40; //40
        int score = 0;

        ALLEGRO_SAMPLE_INSTANCE* sampleInstance;
        ALLEGRO_SAMPLE_INSTANCE* sampleInstanceJump;
        ALLEGRO_EVENT_QUEUE *event_queue;
        ALLEGRO_TIMER *timer;
        ALLEGRO_EVENT ev;
        Sounds *sound;

        DonkeyKong *dk;
        Barrel *barrel;
        Mario *mario;

        Graphic *manager;
    
    public:
        GameManager (ALLEGRO_DISPLAY *display,ALLEGRO_BITMAP *buffer,const int& scaleW,const int& scaleH,const int& scaleX,const int& scaleY);

        ~GameManager ();

        void Menu ();

        void gioco ();
};

#endif