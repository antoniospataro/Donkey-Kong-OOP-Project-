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
        bool premiStart = true;
        bool menu = true;
        bool Esci = false;
        bool redraw = true;
        bool keys[7] = {false, false, false, false, false, false, false};
        bool backGroundMusic = true;
        bool walkSound = false;
        bool change = false;
        bool mute = false;
        bool move = false;
        int FPS = 35; //40
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
        GameManager (ALLEGRO_DISPLAY *display,ALLEGRO_BITMAP *buffer,int scaleW,int scaleH,int scaleX,int scaleY);

        ~GameManager ();

        void Menu ();

        void gioco ();
};

#endif