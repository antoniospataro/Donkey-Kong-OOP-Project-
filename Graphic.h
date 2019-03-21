#include <string>
#include "DonkeyKong.h"
#include "Barrel.h"
#include "Mario.h"
#include <fstream>
#include <iostream>
using namespace std;
#ifndef GRAPHIC_H
#define GRAPHIC_H
const int x = 26;
const int y = 30; 
class Graphic{
        private: 
                int matrix[x][y];
                ALLEGRO_BITMAP* bmp;
                ALLEGRO_BITMAP* buffer;
                ALLEGRO_DISPLAY *display;
                int s_y;
                int s_x;
                int scale_w;
                int scale_h;
                int scale_x;
                int scale_y; 
        public:
                Graphic(const int &scale_w, const int &scale_h, const int &scale_x, const int &scale_y, ALLEGRO_BITMAP *buffer, ALLEGRO_DISPLAY *display){
                        fstream input;
                        input.open("Map.txt");
                        if (input.is_open())
                                for (int i=0;i<x;i++)
                                        for (int j=0;j<y;j++)
                                                input >> matrix[i][j];
	                input.close();
                        this->scale_h = scale_h;
                        this->scale_w = scale_w;
                        this->scale_x = scale_x;
                        this->scale_y = scale_y;
                        this->buffer = buffer;
                        this->display = display;
                }
                void setDk(DonkeyKong& dk){
                        for (int i=0;i<x;i++)
                                for (int j=0;j<y;j++)
                                if(matrix[i][j]==3&&matrix[i][j+1]==0&&matrix[i+2][j]==3){
                                        dk.setX((j+1)*8);
	                                dk.setY((i)*8);
                                }
                }
                void drawMap ()
                {
                        al_set_target_bitmap(buffer);
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                        ALLEGRO_BITMAP *bitmap = NULL;
                        
                        for (int i=0;i<x;i++)
                                for (int j=0;j<y;j++)
                                {
                                        switch (matrix[i][j])
                                        {
                                                case 1:
                                                        bmp=al_load_bitmap("Sprites/floor.png");
                                                        al_draw_bitmap(bmp,j*8,i*8,0);
                                                        al_destroy_bitmap(bmp);
                                                        break;
                                                case 2:
                                                        bmp=al_load_bitmap("Sprites/scale.png");
                                                        al_draw_bitmap(bmp,j*8,i*8,0);
                                                        al_destroy_bitmap(bmp);
                                                        break;
                                                case 3:
                                                        bmp=al_load_bitmap("Sprites/Barrel0.png");
                                                        al_draw_bitmap(bmp,j*8,i*8,0);
                                                        al_destroy_bitmap(bmp);        
                                                default:
                                                        break;
                                        }                
                                }
                        al_set_target_backbuffer(this->display);
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                        al_draw_scaled_bitmap(buffer, 0, 0,(y*8) ,(x*8), scale_x, scale_y, scale_w, scale_h, 0);

                }   
                void DrawDK(DonkeyKong& dk){
                        al_set_target_bitmap(buffer);
                        dk.Draw();
                        al_set_target_backbuffer(this->display);
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                        al_draw_scaled_bitmap(buffer, 0, 0,(y*8) ,(x*8), scale_x, scale_y, scale_w, scale_h, 0);

                }
                 void DrawMario(Mario& m,int&pos_x,int&pos_y){
                        al_set_target_bitmap(buffer);
                        m.Draw(pos_x,pos_y); 
                        al_set_target_backbuffer(this->display);
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                        al_draw_scaled_bitmap(buffer, 0, 0,(y*8) ,(x*8), scale_x, scale_y, scale_w, scale_h, 0);
                }
                void DrawBarrel(){
                        al_set_target_bitmap(buffer);
                        
                        al_set_target_backbuffer(this->display);
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                        al_draw_scaled_bitmap(buffer, 0, 0,(y*8) ,(x*8), scale_x, scale_y, scale_w, scale_h, 0);
                }
                ~Graphic(){}   
};
#endif