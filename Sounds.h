#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

class Sounds {
    private:
        ALLEGRO_SAMPLE *sample;
        ALLEGRO_SAMPLE *sampleBackground;
        ALLEGRO_SAMPLE_INSTANCE* sampleInstance;

    public:
        Sounds() {
            sample = NULL;
            sampleInstance = NULL;
            sampleBackground = al_load_sample("SoundGame/bacmusic2.wav");
        }

        ALLEGRO_SAMPLE* getSoundDeath(){
            al_destroy_sample(sample);
            sample = al_load_sample("SoundGame/death.wav");
            return sample;
        }
        ALLEGRO_SAMPLE* getSoundBack(){
            return sampleBackground;
        }
        ALLEGRO_SAMPLE* getSoundHammer(){
            al_destroy_sample(sample);
            sample = al_load_sample("SoundGame/hammer.wav");
            return sample;
        }
        ALLEGRO_SAMPLE* getSoundJump(){
            al_destroy_sample(sample);
            sample = al_load_sample("SoundGame/jump2.wav");
            return sample;
        }
        ALLEGRO_SAMPLE* getSoundWin(){
            al_destroy_sample(sample);
            sample = al_load_sample("SoundGame/win2.wav");
            return sample;
        }
        ALLEGRO_SAMPLE* getSoundWalk(){
            al_destroy_sample(sample);
            sample = al_load_sample("SoundGame/walking.wav");
            return sample;
        }
        

        ~Sounds (){
            al_destroy_sample(sample);
            al_destroy_sample(sampleBackground);
        }
        
};