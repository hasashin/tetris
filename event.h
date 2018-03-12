#ifndef TETRIS_LOOP_H
#define TETRIS_LOOP_H
#include <allegro5/display.h>
#include <allegro5/keyboard.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>

static void *eventLoop(ALLEGRO_THREAD *th, void *data) {
    auto evHnd = (EVENT_HANDLER *) data;
    bool end = false;
    while (!end) {
        al_get_keyboard_state(evHnd->keyboard);
        if (!al_event_queue_is_empty(evHnd->queue)) {
            al_get_next_event(evHnd->queue, evHnd->event);
            switch (evHnd->event->type) {
                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                    evHnd->control->close = true;
                    end = true;
                    break;
                case ALLEGRO_EVENT_KEY_DOWN:
                    switch (evHnd->event->keyboard.keycode) {
                        case ALLEGRO_KEY_ESCAPE:
                            if(evHnd->control->state == PS_MENU && evHnd->control->menutype != MT_MAIN){
                                if(evHnd->control->enableSounds) evHnd->control->audio1.playMenuSelect();
                                evHnd->menu->setActiveElement(evHnd->menu->getElementsCount()-1);
                                evHnd->control->enter = true;
                            }
                            break;
                        case ALLEGRO_KEY_DOWN:
                            if(evHnd->control->state == PS_MENU){
                                if(evHnd->control->enableSounds) evHnd->control->audio1.playMenuToggle();
                                evHnd->control->menutoggle = MTT_DOWN;
                            }
                            break;
                        case ALLEGRO_KEY_UP:
                            if(evHnd->control->state == PS_MENU){
                                if(evHnd->control->enableSounds) evHnd->control->audio1.playMenuToggle();
                                evHnd->control->menutoggle = MTT_UP;
                            }
                            break;
                        case ALLEGRO_KEY_ENTER:
                            if(evHnd->control->state == PS_MENU && evHnd->control->enableSounds)
                                evHnd->control->audio1.playMenuSelect();
                            evHnd->control->enter = true;
                        default:
                            break;
                    }
                default:
                    break;
            }
        }
        if(evHnd->control->close) return nullptr;
    }
    return nullptr;
}

#endif //TETRIS_LOOP_H
