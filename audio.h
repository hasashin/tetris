#ifndef TETRIS_AUDIO_H
#define TETRIS_AUDIO_H
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <iostream>

class audio{
    ALLEGRO_VOICE* voice1 = al_create_voice(44100,ALLEGRO_AUDIO_DEPTH_INT16,ALLEGRO_CHANNEL_CONF_2);
    ALLEGRO_MIXER* mixer1 = al_create_mixer(44100,ALLEGRO_AUDIO_DEPTH_FLOAT32,ALLEGRO_CHANNEL_CONF_2);
    ALLEGRO_SAMPLE* menuToggle = al_load_sample("sound/menu.wav");
    ALLEGRO_SAMPLE* menuSelect = al_load_sample("sound/menuSelect.wav");
public:
    audio(){
        al_attach_mixer_to_voice(mixer1,voice1);
    }
    void playMenuToggle(){
        auto instance1 = al_create_sample_instance(menuToggle);
        auto instance2 = al_create_sample_instance(menuToggle);
        al_attach_sample_instance_to_mixer(instance1,mixer1);
        al_attach_sample_instance_to_mixer(instance2,mixer1);

        al_set_sample_instance_playing(instance1,true);
        al_set_sample_instance_playing(instance2,true);
    }
    void playMenuSelect(){
        auto instance1 = al_create_sample_instance(menuSelect);
        auto instance2 = al_create_sample_instance(menuSelect);
        al_attach_sample_instance_to_mixer(instance1,mixer1);
        al_attach_sample_instance_to_mixer(instance2,mixer1);

        al_set_sample_instance_playing(instance1,true);
        al_set_sample_instance_playing(instance2,true);
    }
    ~audio(){
        al_destroy_sample(menuToggle);
        al_destroy_mixer(mixer1);
        al_destroy_voice(voice1);
    }
};


#endif //TETRIS_AUDIO_H
