#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <string>
#include "DonkeyKong.h"
#include "Barrel.h"
#include "Mario.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <stdio.h>

using namespace std;

enum KEYS{ UP, DOWN, LEFT, RIGHT, SPACE, ENTER,ESCAPE};
class Graphic{
        private: 
                int matrix[100][100];
                ALLEGRO_BITMAP* bmp;
                ALLEGRO_BITMAP* buffer;
                ALLEGRO_DISPLAY *display;
                ALLEGRO_FONT* font;
                int s_y;
                int s_x;
                int scale_w;
                int scale_h;
                int scale_x;
                int scale_y; 
                int level;
                bool win;
                bool death;
                vector<Barrel> barrels;
        public:
                Graphic (int scaleW,int scaleH,int scaleX,int scaleY,ALLEGRO_BITMAP *buffer,ALLEGRO_DISPLAY *display);
                void drawMenu (bool start);
                void setDk(DonkeyKong& dk);
                void setMario(Mario& m);
                void drawMap();
                void drawDK(DonkeyKong& dk);
                void drawBarrels(Mario& m);
                void drawMario(Mario& m,DonkeyKong& dk);

                bool getWin ();

                void setWin (bool ok);

                bool getDeath();

                void setDeath(bool ok);

		void setMap(Mario& m,DonkeyKong& dk);
                void setThisMap(Mario& m);

                void drawLife (int score);
                void drawScore (const int& score);
                ~Graphic();   
};
#endif