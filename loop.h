//
// Created by Dominik Hażak on 09.03.2018.
//
#ifndef TETRIS_LOOP_H
#define TETRIS_LOOP_H


void mainMenuLoop(ALLEGRO_DISPLAY* disp, sterowanie *control) {
    Menu menu(control->menutype,control);
    bool e = true;
    auto titleFont = al_load_ttf_font("fonts/title.ttf",int(0.3*control->res.getHeight()),0);
    while (e && !control->close) {
        al_clear_to_color(al_map_rgb(0,0,0));
        if(!titleFont) titleFont = al_create_builtin_font();
        al_draw_text(titleFont,
                     al_map_rgb(40,234,132),
                     0.3f*control->res.getWidth(),
                     0.2f*control->res.getHeight(),
                     0,
                     "TETRIS"
        );

        menu.changeActiveElement(&(control->menutoggle));
        menu.displayMenu();
        if(control->enter) {
            if(menu.getActiveElement()->getName() == "newgame"){
                control->state = PS_INGAME;
                e=false;
            }
            if (menu.getActiveElement()->getName() == "settings") {
                control->menutype = MT_SETTINGS;
                menu.changeMenuType(control->menutype);
            }
            if (menu.getActiveElement()->getName() == "close") {
                control->close = true;
            }
            if(menu.getActiveElement()->getName() == "backfromsettings"){
                control->menutype = MT_MAIN;
                menu.changeMenuType(control->menutype);
            }
            if(menu.getActiveElement()->getName() == "resolution"){
                control->menutype = MT_RES;
                menu.changeMenuType(control->menutype);
            }
            if(menu.getActiveElement()->getName() == "backfromres"){
                control->menutype = MT_SETTINGS;
                menu.changeMenuType(control->menutype);
            }
            if(menu.getActiveElement()->getName() == "800x600"){
                control->res.changeResolution(RES_800X600,disp);
            }
            if(menu.getActiveElement()->getName() == "1024x768"){
                control->res.changeResolution(RES_1024X768,disp);
            }
            if(menu.getActiveElement()->getName() == "1280x720"){
                control->res.changeResolution(RES_1280X720,disp);
            }
            if(menu.getActiveElement()->getName() == "1366x768"){
                control->res.changeResolution(RES_1366X768,disp);
            }
            if(menu.getActiveElement()->getName() == "1600x900"){
                control->res.changeResolution(RES_1600X900,disp);
            }
            if(menu.getActiveElement()->getName() == "1920x1080"){
                control->res.changeResolution(RES_1920X1080,disp);
            }

            control->enter = false;
        }
        al_flip_display();
    }
    al_destroy_font(titleFont);
}

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
                            evHnd->control->close = true;
                            end = true;
                            break;
                        case ALLEGRO_KEY_DOWN:
                            if(evHnd->control->state == PS_MENU){
                                evHnd->control->menutoggle = MTT_DOWN;
                            }
                            break;
                        case ALLEGRO_KEY_UP:
                            if(evHnd->control->state == PS_MENU){
                                evHnd->control->menutoggle = MTT_UP;
                            }
                            break;
                        case ALLEGRO_KEY_ENTER:
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
