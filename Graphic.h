#include <string>
#include "DonkeyKong.h"
#include "Barrel.h"
#include "Mario.h"
#include <fstream>
#include <iostream>
using namespace std;
#ifndef GRAPHIC_H
#define GRAPHIC_H
int x;
int y; 
int pixel=16;
enum KEYS{ UP, DOWN, LEFT, RIGHT, SPACE, ENTER,ESCAPE};
class Graphic{
        private: 
                int matrix[100][100];
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
                Graphic(int level, const int &scale_w, const int &scale_h, const int &scale_x, const int &scale_y, ALLEGRO_BITMAP *buffer, ALLEGRO_DISPLAY *display){
                        fstream input;
                        if(level==1)
                                input.open("Map1.map");
                        if(level==2)
                                input.open("Map2.map");
                        if (input.is_open())
                                input>> x >> y;
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
                void drawMenu (bool start)
                {
                        al_set_target_bitmap(buffer);
                        bmp = al_load_bitmap("Sprites/dk.png");
                        al_draw_bitmap(bmp,(pixel*x)/2,(pixel*y)/500,0);
                        al_destroy_bitmap(bmp);
                        if (start)
                        {
                                bmp = al_load_bitmap("Sprites/Start1.png");
                                al_draw_bitmap(bmp,(pixel*x)/2,(pixel*y)/3,0);
                                al_destroy_bitmap(bmp);

                                bmp = al_load_bitmap("Sprites/Exit2.png");
                                al_draw_bitmap(bmp,(pixel*x)/2,(pixel*y)/2,0);
                                al_destroy_bitmap(bmp);
                        }
                        if (!start)
                        {
                                bmp = al_load_bitmap("Sprites/Start2.png");
                                al_draw_bitmap(bmp,(pixel*x)/2,(pixel*y)/3,0);
                                al_destroy_bitmap(bmp);

                                bmp = al_load_bitmap("Sprites/Exit1.png");
                                al_draw_bitmap(bmp,(pixel*x)/2,(pixel*y)/2,0);
                                al_destroy_bitmap(bmp);
                        }

                        al_set_target_backbuffer(this->display);
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                        al_draw_scaled_bitmap(buffer, 0, 0,(y*pixel) ,(x*pixel), scale_x, scale_y, scale_w, scale_h, 0);
                }
                void setDk(DonkeyKong& dk){
                        for (int i=0;i<x;i++)
                                for (int j=0;j<y;j++)
                                if(matrix[i][j]==3&&matrix[i][j+1]==3){
                                        dk.setX((j+2)*pixel);
	                                dk.setY((i-2)*pixel);
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
                                                        bmp=al_load_bitmap("Sprites/Floor.png");
                                                        al_draw_bitmap(bmp,j*pixel,i*pixel,0);
                                                        al_destroy_bitmap(bmp);
                                                        break;
                                                case 2:
                                                        bmp=al_load_bitmap("Sprites/Scale.png");
                                                        al_draw_bitmap(bmp,j*pixel,i*pixel,0);
                                                        al_destroy_bitmap(bmp);
                                                        break;
                                                case 3:
                                                        bmp=al_load_bitmap("Sprites/Barrel0.png");
                                                        al_draw_bitmap(bmp,j*pixel,i*pixel,0);
                                                        al_destroy_bitmap(bmp);        
                                                default:
                                                        break;
                                        }                
                                }
                        al_set_target_backbuffer(this->display);
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                        al_draw_scaled_bitmap(buffer, 0, 0,(y*pixel) ,(x*pixel), scale_x, scale_y, scale_w, scale_h, 0);

                }   
                void drawDK(DonkeyKong& dk){
                        al_set_target_bitmap(buffer);
                        dk.Draw();
                        al_set_target_backbuffer(this->display);
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                        al_draw_scaled_bitmap(buffer, 0, 0,(y*pixel) ,(x*pixel), scale_x, scale_y, scale_w, scale_h, 0);

                }
                void drawMario(Mario& m){
                        al_set_target_bitmap(buffer);
                        if(m.getJump())
                        {
                                if(m.getSpace())
                                        m.setSpace(false);
                                m.setJmp(m.getJmp()+1);
                                bmp=al_load_bitmap("Sprites/Walk2.png");
                                if(m.getRight())
                                {
                                        if(m.getJmp()!=2&&m.getX()!=y*pixel-16){
                                                m.setY(m.getY()-8);
                                                m.setX(m.getX()+8); }                                              
                                        al_draw_bitmap(bmp,m.getX(),m.getY(),ALLEGRO_FLIP_HORIZONTAL);
                                }
                                else if(m.getLeft()){
                                        if(m.getJmp()!=2&&m.getX()!=0){/*togliere se si vuole lasciare in aria un solo frame*/
                                                m.setY(m.getY()-8);
                                                m.setX(m.getX()-8);}
                                        al_draw_bitmap(bmp,m.getX(),m.getY(),0);

                                }
                                else{
                                        if(m.getJmp()!=2) /*togliere se si vuole lasciare in aria un solo frame*/
                                                m.setY(m.getY()-8);
                                        if(m.getReverse())
                                                al_draw_bitmap(bmp,m.getX(),m.getY(),ALLEGRO_FLIP_HORIZONTAL);
                                        else
                                                al_draw_bitmap(bmp,m.getX(),m.getY(),0);
                                }
                                if(m.getJmp()==2){ /*togliere se si vuole lasciare in aria un solo frame*/
                                        m.setJump(false);}
                                m.setFall(true);
                                al_destroy_bitmap(bmp);
                        }
                        else if(m.getFall()&&m.getReverse())
                        {
                                m.setJmp(m.getJmp()+1);
                                if(m.getSpace())
                                        m.setSpace(false);
                                m.setY(m.getY()+8);
                                if(m.getRight()&&m.getX()!=(y*16)-16&&(m.getJmp()==3||m.getJmp()==4)){
                                        m.setX(m.getX()+8);
                                        m.setRight(false);}
                                else if(m.getLeft()&&m.getX()!=0&&(m.getJmp()==3||m.getJmp()==4)){
                                        m.setX(m.getX()-8);
                                        m.setLeft(false);}
                                m.Draw(true);
                                if(m.getY()%16==0&&matrix[m.getY()/16+1][m.getX()/16]==1){
                                      m.setFall(false);m.setJmp(0);}
                        }
                        else if(m.getFall()&&m.getReverse()==false){
                                m.setJmp(m.getJmp()+1);
                                if(m.getSpace())
                                        m.setSpace(false);
                                m.setY(m.getY()+8);
                                if(m.getRight()&&m.getX()!=(y*16)-16&&(m.getJmp()==3||m.getJmp()==4)){
                                        m.setX(m.getX()+8);
                                        m.setRight(false);}
                                else if(m.getLeft()&&m.getX()!=0&&(m.getJmp()==3||m.getJmp()==4)){
                                        m.setX(m.getX()-8);
                                        m.setLeft(false);}
                                m.Draw(false);
                                if(m.getY()%16==0&&matrix[m.getY()/16+1][m.getX()/16]==1){
                                      m.setFall(false);m.setJmp(0);}
                        }
                        else if(m.getSpace()){
                                m.setSpace(false);
                                if(m.getFall()==false&&m.getJump()==false){
                                        m.setJump(true);
                                        // cout<<m.getX()/16<<" "<<m.getY()/16;
                                        if(m.getReverse()){
                                                if(m.getRight()&&m.getX()!=(y*16)-16){
                                                        m.setY(m.getY()-8);
                                                        m.setX(m.getX()+8);
                                                }
                                                else 
                                                        m.setY(m.getY()-8);                                               
                                                bmp=al_load_bitmap("Sprites/Walk2.png");
                                                al_draw_bitmap(bmp,m.getX(),m.getY(),ALLEGRO_FLIP_HORIZONTAL);
                                        }
                                        else{
                                                if(m.getLeft()&&m.getX()!=0){
                                                        m.setY(m.getY()-8);
                                                        m.setX(m.getX()-8);
                                                }
                                                else 
                                                         m.setY(m.getY()-8);  
                                                bmp=al_load_bitmap("Sprites/Walk2.png");
                                                al_draw_bitmap(bmp,m.getX(),m.getY(),0);
                                        }
                                        al_destroy_bitmap(bmp);
                                }                                
                        }
                        else if(m.getRight()&&m.getFall()==false/*&&!m.getScale()*/)
                        {
                                m.setReverse(true);
                                if(m.getX()!=(y*16)-16/*&&m.getY()%16==0*/)/*DIVERSO DA FINE SCHERMO*/{
                                        if(m.getY()%16==0 && matrix[m.getY()/16+1][m.getX()/16]==1 && m.getScale())
                                                m.setScale(false);
                                        if(!m.getScale()){
                                                m.setX(m.getX()+8);
                                                m.setCont(m.getCont()+1);
                                                if(m.getCont()==1)
                                                        bmp=al_load_bitmap("Sprites/Walk1.png");
                                                else{
                                                        bmp=al_load_bitmap("Sprites/Walk2.png");m.setCont(0);}                                                
                                        }
                                        else{
                                             m.setX(m.getX()+8);
                                                m.setCont(m.getCont()+1);
                                                if(m.getCont()==1)
                                                        bmp=al_load_bitmap("Sprites/Climbing1.png");
                                                else{
                                                        bmp=al_load_bitmap("Sprites/Climbing2.png");m.setCont(0);}   
                                        }
                                        al_draw_bitmap(bmp,m.getX(),m.getY(),ALLEGRO_FLIP_HORIZONTAL);
                                        if((m.getX()%16==0 && matrix[(m.getY()/16)+1][m.getX()/16]==0)||(m.getY()%16!=0 && matrix[m.getY()/16+1][m.getX()/16]==1 && matrix[m.getY()/16][m.getX()/16]==0 && matrix[m.getY()/16+2][m.getX()/16]==0)){
                                                m.setFall(true);
                                                if(m.getScale())
                                                        m.setScale(false);
                                        }
                                        al_destroy_bitmap(bmp);
                                }
                                else if(m.getX()==(y*16)-16)
                                        m.Draw(true);
                                m.setRight(false);
                        }
                        else if(m.getLeft()&&m.getFall()==false/*&&!m.getScale()*/)
                        {
                                m.setReverse(false);
                                if(m.getX()!=0/*&&m.getY()%16==0*/)/*DIVERSO DA FINE SCHERMO SINISTRO*/{
                                        if(m.getY()%16==0 && matrix[m.getY()/16+1][m.getX()/16]==1 && m.getScale())
                                                m.setScale(false);
                                        if(!m.getScale()){
                                                m.setX(m.getX()-8);
                                                m.setCont(m.getCont()+1);
                                                if(m.getCont()==1)
                                                        bmp=al_load_bitmap("Sprites/Walk1.png");
                                                else{
                                                        bmp=al_load_bitmap("Sprites/Walk2.png");
                                                        m.setCont(0);}
                                        }
                                        else{
                                                m.setX(m.getX()-8);
                                                m.setCont(m.getCont()+1);
                                                if(m.getCont()==1)
                                                        bmp=al_load_bitmap("Sprites/Climbing1.png");
                                                else{
                                                        bmp=al_load_bitmap("Sprites/Climbing2.png");
                                                        m.setCont(0);}
                                        }        
                                        if((m.getX()%16==0 && matrix[(m.getY()/16)+1][m.getX()/16]==0)||(m.getX()%16==0 && m.getY()%16!=0 && matrix[m.getY()/16][m.getX()/16]==0 && matrix[m.getY()/16+1][m.getX()/16]==1 && matrix[m.getY()/16+2][m.getX()/16]==0)){
                                              m.setFall(true);
                                              if(m.getScale())
                                                      m.setScale(false);
                                        }
                                        al_draw_bitmap(bmp,m.getX(),m.getY(),0);
                                        al_destroy_bitmap(bmp);

                                }
                                else if(m.getX()==0)
                                        m.Draw(false);
                                m.setLeft(false);
                        }
                        else if((m.getUp()&&m.getFall()==false)){                        
                                if(((matrix[m.getY()/16][m.getX()/16]==2 || matrix[m.getY()/16][m.getX()/16]==1)   || (matrix[(m.getY()+8)/16][m.getX()/16]==2 || matrix[(m.getY()+8)/16][m.getX()/16]==1))||(m.getX()%16!=0&&((matrix[m.getY()/16][m.getX()/16+1]==2 || matrix[m.getY()/16][m.getX()/16+1]==1)   || (matrix[(m.getY()+8)/16][m.getX()/16+1]==2 || matrix[(m.getY()+8)/16][m.getX()/16+1]==1)))){
                                        m.setScale(true);
                                        m.setY(m.getY()-8);
                                        m.setCont(m.getCont()+1);
                                        if(m.getCont()==1)
                                                bmp=al_load_bitmap("Sprites/Climbing1.png");
                                        else{
                                                bmp=al_load_bitmap("Sprites/Climbing2.png");
                                                m.setCont(0);
                                        }
                                        al_draw_bitmap(bmp,m.getX(),m.getY(),0);
                                        al_destroy_bitmap(bmp);
                                }
                                else{
                                        if(m.getReverse())
                                                m.Draw(true);
                                        else
                                                m.Draw(false);
                                }
                                
                                m.setUp(false);
                        }
                        else if(m.getDown()&&m.getFall()==false){
                                if((matrix[m.getY()/16][m.getX()/16]==2&&matrix[m.getY()/16+1][m.getX()/16]!=1)||(matrix[m.getY()/16][m.getX()/16]==0&&matrix[m.getY()/16+1][m.getX()/16]==1&&matrix[m.getY()/16+2][m.getX()/16]==2)||(matrix[m.getY()/16][m.getX()/16]==1&&matrix[m.getY()/16+1][m.getX()/16]==2)||(matrix[m.getY()/16][m.getX()/16+1]==2&&matrix[m.getY()/16+1][m.getX()/16+1]!=1)||(m.getX()%16!=0&&matrix[m.getY()/16][m.getX()/16+1]==0&&matrix[m.getY()/16+1][m.getX()/16+1]==1&&matrix[m.getY()/16+2][m.getX()/16+1]==2)||(matrix[m.getY()/16][m.getX()/16+1]==1&&matrix[m.getY()/16+1][m.getX()/16+1]==2)&&m.getX()%16!=0){
                                        m.setScale(true);
                                        m.setY(m.getY()+8);
                                        m.setCont(m.getCont()+1);
                                        if(m.getCont()==1)
                                                bmp=al_load_bitmap("Sprites/Climbing1.png");
                                        else{
                                                bmp=al_load_bitmap("Sprites/Climbing2.png");
                                                m.setCont(0);
                                        }
                                        al_draw_bitmap(bmp,m.getX(),m.getY(),0);
                                        al_destroy_bitmap(bmp);
                                }
                                else{
                                        if(m.getReverse()) 
                                                m.Draw(true);
                                        else 
                                                m.Draw(false);
                                }
                                m.setDown(false);
                                
                        }
                        else if(m.getScale())
                        {
                                if(m.getCont()==1)
                                        bmp=al_load_bitmap("Sprites/Climbing1.png");
                                else{
                                        bmp=al_load_bitmap("Sprites/Climbing2.png");
                                        m.setCont(0);
                                }
                                al_draw_bitmap(bmp,m.getX(),m.getY(),0);
                                if(m.getY()%16==0 && matrix[m.getY()/16][m.getX()/16]==2&&matrix[(m.getY()/16)+1][m.getX()/16]==1)
                                        m.setScale(false);        
                                else if(m.getY()%16==0 && matrix[m.getY()/16][m.getX()/16]==0&&matrix[(m.getY()/16)+1][m.getX()/16]==1)
                                        m.setScale(false);
                        }
                        else if(m.getReverse())
                                m.Draw(true);
                        else
                                m.Draw(false);
                        al_set_target_backbuffer(this->display);
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                        al_draw_scaled_bitmap(buffer, 0, 0,(y*pixel) ,(x*pixel), scale_x, scale_y, scale_w, scale_h, 0);
                }
                void DrawBarrel(){
                        al_set_target_bitmap(buffer);
                        
                        al_set_target_backbuffer(this->display);
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                        al_draw_scaled_bitmap(buffer, 0, 0,(y*pixel) ,(x*pixel), scale_x, scale_y, scale_w, scale_h, 0);
                }
                ~Graphic(){}   
};
#endif