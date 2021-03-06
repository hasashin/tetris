#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include "audio.h"
#include "controlObjects.h"
#include "event.h"
#include "menu.h"
#include "gameObjects.h"


int main(int argc,char** argv) {
    al_init();
    al_install_keyboard();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_audio();
    al_init_acodec_addon();

    auto control = new sterowanie;
    ALLEGRO_DISPLAY* disp = al_create_display(control->res.getWidth(),control->res.getHeight());
    control->disp = disp;
    auto event = new ALLEGRO_EVENT;
    ALLEGRO_EVENT_QUEUE* kolejka = al_create_event_queue();
    auto st = new ALLEGRO_KEYBOARD_STATE;
    auto eventGroup = new EVENT_HANDLER(kolejka,event,control,st);
    auto thread1 = al_create_thread(eventLoop,eventGroup);
    ALLEGRO_FONT * fnt = al_create_builtin_font();

    al_set_window_title(disp,"Tetris");
    al_register_event_source(kolejka,al_get_display_event_source(disp));
    al_register_event_source(kolejka,al_get_keyboard_event_source());
    al_get_keyboard_state(st);
    al_start_thread(thread1);
    while(!control->close){
        al_clear_to_color(al_map_rgb(0,0,0));
        switch(control->state) {
            case PS_MENU:
                mainMenuLoop(control,eventGroup);
                break;
            default:
                al_draw_text(fnt,al_map_rgb(255,50,50),10,50,0,"Niepoprawny stan programu, uruchom ponownie grę");
                al_flip_display();
                break;
        }
        al_get_keyboard_state(st);
    }
    delete control;
    al_uninstall_audio();
    al_destroy_thread(thread1);
    al_destroy_display(disp);
    al_shutdown_font_addon();
    al_shutdown_ttf_addon();
    al_uninstall_keyboard();
    return 0;
}