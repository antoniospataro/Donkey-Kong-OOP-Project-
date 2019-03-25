/*$(pkg-config allegro-5 allegro_font-5 allegro_image-5 allegro_memfile-5 allegro_ttf-5 allegro_physfs-5 allegro_dialog-5 allegro_video-5 allegro_acodec-5 allegro_main-5 allegro_primitives-5 allegro_audio-5 --libs --cflags) */
#include<allegro5/allegro.h>
#include<allegro5/allegro_image.h>
#include "Graphic.h"
#include<algorithm>
#include "Mario.h"
extern int barx, bary; 
using namespace std;
//enum KEYS{ UP, DOWN, LEFT, RIGHT};
//x=112 y=88
int main(int argc, char **argv)
{
	int screenWidth=pixel*37; //30 w
	int screenHeight=pixel*24; //26 h
	bool Esci = false;
	bool menu = true;
	bool redraw = true;
	int FPS = 30; //30
	bool keys[6] = {false, false, false, false, false, false};
	//cout<<x<<" "<<y;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	if(!al_init())										//initialize Allegro
		return -1;
    	al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
	ALLEGRO_DISPLAY *display = al_create_display(screenWidth,screenHeight);
   	if(!display){
        cout << "Fatal error, unable to create a display";
        return -1;
    	}
    	ALLEGRO_BITMAP *buffer = al_create_bitmap(screenWidth,screenHeight);
    	if(!buffer){
        cout << "Fatal error, unable to create a buffer";
        return -1;
    	}
	int windowHeight = al_get_display_height(display);
    	int windowWidth = al_get_display_width(display);
    	float sx = windowWidth / float(screenWidth);
    	float sy = windowHeight / float(screenHeight);
    	int scale = std::min(sx, sy);
    	int scaleW = screenWidth * scale;
    	int scaleH = screenHeight * scale;
    	int scaleX = (windowWidth - scaleW) / 2;
    	int scaleY = (windowHeight - scaleH) / 2;
	al_set_target_bitmap(buffer);
 	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_install_keyboard();
	if(!al_init_image_addon()){cout<<"NUOH FAZIO";return -1;}
	event_queue = al_create_event_queue();
	timer = al_create_timer(3.0/FPS);
	int matrix[x][y];
	
	DonkeyKong dk(0,0);
	Barrel barrel(0,0);
	Mario mario(/*(rand()%28)*8*/3*pixel,19*pixel);
	//cout<<matrix[23][14]; PRIMA SCALA
	Graphic manager(1,scaleW, scaleH, scaleX, scaleY, buffer, display);
	manager.setDk(dk);
	int pos_x=0;
	int pos_y=0;
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_start_timer(timer);
	ALLEGRO_EVENT ev;

	while (menu)
	{
		al_wait_for_event(event_queue,&ev);

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
				case ALLEGRO_KEY_UP:
					keys[UP] = true;
					break;
				case ALLEGRO_KEY_DOWN:
					keys[DOWN] = true;
					break;
				case ALLEGRO_KEY_ENTER:  
					keys[ENTER] = true;
					break;
				default:
					break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
				case ALLEGRO_KEY_UP:
					keys[UP] = false;
					break;
				case ALLEGRO_KEY_DOWN:
					keys[DOWN] = false;
					break;
				case ALLEGRO_KEY_ESCAPE:
					keys[ESCAPE] = true;
					break;
				default:
					break;
			}
		}

		else if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			if (keys[ENTER])
			{
				menu = false;
			}
			redraw = true;
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			menu = false;
			Esci = true;
		}
		if (keys[ESCAPE])
		{
			menu = false;
			Esci = true;
		}

		else if (redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;
			manager.drawMenu();
			al_flip_display();
		}

	}


	while(!Esci)
	{
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(ev.keyboard.keycode)
			{
				case ALLEGRO_KEY_UP:
					keys[UP] = true;			
					break;
				case ALLEGRO_KEY_DOWN:
					keys[DOWN] = true;
					break;
				case ALLEGRO_KEY_RIGHT:
					keys[RIGHT] = true;
					break;
				case ALLEGRO_KEY_LEFT:
					keys[LEFT] = true;
					break;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(ev.keyboard.keycode)
			{
				case ALLEGRO_KEY_UP:
					keys[UP] = false;
					break;
				case ALLEGRO_KEY_DOWN:
					keys[DOWN] = false;
					break;
				case ALLEGRO_KEY_RIGHT:
					keys[RIGHT] = false;
					break;
				case ALLEGRO_KEY_LEFT:
					keys[LEFT] = false;
					break;
				case ALLEGRO_KEY_ESCAPE:
					Esci = true;
					break;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			Esci = true;
		}
		
			if(ev.type == ALLEGRO_EVENT_TIMER)
			{
				if(keys[UP]){
					mario.setUp(true);
					mario.setDown(false);
					mario.setLeft(false);
					mario.setRight(false);}
				if(keys[DOWN]){
					mario.setDown(true);
					mario.setUp(false);
					mario.setLeft(false);
					mario.setRight(false);}
				if(keys[LEFT]){
					mario.setLeft(true);
					mario.setDown(false);
					mario.setUp(false);
					mario.setRight(false);}
				if(keys[RIGHT]){
					mario.setRight(true);
					mario.setLeft(false);
					mario.setDown(false);
					mario.setUp(false);}
				if(mario.getFall()){
					mario.setLeft(false);
					mario.setDown(false);
					mario.setUp(false);
					mario.setRight(false);}
				redraw = true;
			}
		if(redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;
			manager.drawMap();
			manager.drawDK(dk);
			manager.drawMario(mario);
			//al_draw_porcofazioh;
            al_flip_display();
		}
	}
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_display(display);						//destroy our display object

	return 0;
}