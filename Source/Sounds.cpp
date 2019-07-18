#include "../Headers/Sounds.h"

Sounds::Sounds()
{
    al_reserve_samples(5);
    game = al_load_sample("../Sounds/bacmusic2.wav");
    death = al_load_sample("../Sounds/death.wav");
    win = al_load_sample("../Sounds/win2.wav");
    walking = al_load_sample("../Sounds/walking2.wav");
    jump = al_load_sample("../Sounds/jump.wav");
    walkingInstance = al_create_sample_instance(walking);
    jumpInstance= al_create_sample_instance(jump);
    al_attach_sample_instance_to_mixer(walkingInstance, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(jumpInstance, al_get_default_mixer());
}

void Sounds::startGame()
{
    al_play_sample(game, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
}

void Sounds::playDeath()
{
    al_play_sample(death, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
}

void Sounds::playWin()
{
    al_play_sample(win, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
}

void Sounds::playWalking()
{
    if (!al_get_sample_instance_playing(walkingInstance))
     	al_play_sample_instance(walkingInstance);
}

void Sounds::playJump()
{
    if (!al_get_sample_instance_playing(jumpInstance))    
    al_play_sample_instance(jumpInstance);        
}

void Sounds::stopSounds(){al_stop_samples();}

Sounds::~Sounds()
{
    al_destroy_sample(game);
    al_destroy_sample(death);
    al_destroy_sample_instance(walkingInstance);
    al_destroy_sample(walking);
    al_destroy_sample_instance(jumpInstance);
    al_destroy_sample(jump);
    al_uninstall_audio();
}
