#include "../Headers/GameManager.h"
extern int x;
extern int y;

GameManager::GameManager (ALLEGRO_DISPLAY *display,ALLEGRO_BITMAP *buffer,int scaleW,int scaleH,int scaleX,int scaleY){
    dk = new DonkeyKong(0,0);
    barrel = new Barrel(0,0);
    mario = new Mario(0,0);
    sound = new Sounds(); 
    timer = al_create_timer(2.3/FPS);
    sampleInstance = NULL;
    sampleInstanceJump = NULL;
    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));
    manager = new Graphic(scaleW, scaleH, scaleX, scaleY, buffer, display);
    manager->setMario(*mario);
    manager->setDk(*dk);
}

GameManager::~GameManager (){
    delete manager;
    delete dk;
    delete barrel;
    delete mario;
    delete sound;
}

void GameManager::Menu (){
    al_start_timer(timer);
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
            if (keys[UP])
            {
                premiStart =  true;
            }
            if (keys[DOWN])
            {
                premiStart = false;
            }
            if (keys[ENTER] && premiStart)
            {
                menu = false;
            }
            if (keys[ENTER] && !premiStart)
            {
                menu = false;
                Esci = true;
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
            manager->drawMenu(premiStart);
            al_flip_display();
        }
    }
}

void GameManager:: gioco () {
    while(!Esci)
    {
        al_wait_for_event(event_queue, &ev);
        if (mute){
            manager->setDeath(false);
            sound->stopSounds();
            backGroundMusic = true;
        }
        if (backGroundMusic && !mute){
            sound->startGame();
            backGroundMusic = false;
        }
        if (manager->getWin()){
            if(mute)
                manager->setWin(false);
            else{
                sound->stopSounds();
                sound->playWin();
                al_rest(4);
                manager->setWin(false);
                backGroundMusic=true;
                sound->stopSounds();
            }
        }
        if (manager->getDeath()){
            if(mute)
                manager->setDeath(false);
            else{
                sound->stopSounds();
                sound->playDeath();
                al_rest(4);
                manager->setDeath(false);
                backGroundMusic=true;
                sound->stopSounds();
            }
        }
        if((keys[RIGHT]||keys[LEFT])&&!mute && !mario->getScale())
            sound->playWalking();
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
                case ALLEGRO_KEY_SPACE:
                    keys[SPACE]=true;
                    //if(!mute)
                        //sound->playJump();
                    break;
                case ALLEGRO_KEY_S:
                    change = true;
                    break;
                case ALLEGRO_KEY_M:
                    mute = !mute;
                    break;
                default:
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
                case ALLEGRO_KEY_SPACE:
                    keys[SPACE]=false;
                    break;	
                case ALLEGRO_KEY_ESCAPE:
                    Esci = true;
                    break;
                default:
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
                mario->setUp(true);
                mario->setDown(false);}
            if(keys[DOWN]){
                mario->setDown(true);
                mario->setUp(false);
                mario->setLeft(false);
                mario->setRight(false);}
            if(keys[LEFT]&&!keys[RIGHT]){
                mario->setLeft(true);
                mario->setRight(false);
                mario->setUp(false);
                mario->setDown(false);}
            if(keys[RIGHT]&&!keys[LEFT]){
                mario->setRight(true);
                mario->setLeft(false);
                mario->setUp(false);
                mario->setDown(false);}
            if(keys[SPACE])
                mario->setSpace(true);
            redraw = true;
        }
        if(redraw && al_is_event_queue_empty(event_queue))
        {
            redraw = false;
            if (change){
                manager->setMap(*mario,*dk);
                change = false;
            }
            manager->drawMap();
            manager->drawDK(*dk);
            manager->drawMario(*mario,*dk);
            manager->drawBarrels(*mario,*dk);
            manager->drawLife(mario->getLife());
            al_flip_display();
        }
    }
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
}
