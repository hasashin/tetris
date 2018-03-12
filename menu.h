#ifndef TETRIS_MENU_H
#define TETRIS_MENU_H

void mainMenuLoop(sterowanie *control, EVENT_HANDLER* ev) {
    Menu menu(control->menutype,control);
    ev->menu = &menu;
    bool e = true;
    auto titleFont = al_load_ttf_font("fonts/title.ttf",int(0.3*control->res.getHeight()),0);
    if(!titleFont) titleFont = al_create_builtin_font();

    while (e && !control->close) {
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_text(titleFont,
                     al_map_rgb(40,234,132),
                     0.5f*control->res.getWidth(),
                     0.2f*control->res.getHeight(),
                     ALLEGRO_ALIGN_CENTER,
                     "TETRIS"
        );
        menu.changeActiveElement(&(control->menutoggle));
        int elemCount = menu.getElementsCount();
        if(menu.getElementsCount()>6){
            if(menu.getActiveElement()->getId()<3){
                menu.displayMenu(0);
            }
            else if(menu.getActiveElement()->getId() >= 2 && menu.getActiveElement()->getId() < elemCount-3){
                menu.displayMenu(menu.getActiveElement()->getId()-3);
            }
            else{
                menu.displayMenu(elemCount-6);
            }
        }
        else menu.displayMenu(0);
        if(control->enter) {
            if(menu.getActiveElement()->getName() == "newgame"){
                control->state = PS_INGAME;
                e=false;
            }else
            if (menu.getActiveElement()->getName() == "settings") {
                control->menutype = MT_SETTINGS;
                menu.changeMenuType(control->menutype);
            }else
            if (menu.getActiveElement()->getName() == "close") {
                control->close = true;
            } else
            if(menu.getActiveElement()->getName() == "backfromsettings"){
                control->menutype = MT_MAIN;
                menu.changeMenuType(control->menutype);
            } else
            if(menu.getActiveElement()->getName() == "resolution"){
                control->menutype = MT_RES;
                menu.changeMenuType(control->menutype);
            } else
            if(menu.getActiveElement()->getName() == "music"){
                control->menutype = MT_MUSIC;
                menu.changeMenuType(control->menutype);
            } else
            if(menu.getActiveElement()->getName() == "backfromres"){
                control->menutype = MT_SETTINGS;
                menu.changeMenuType(control->menutype);
            } else
            if(menu.getActiveElement()->getName() == "fullscreen"){
                al_set_display_flag(control->disp,
                                    ALLEGRO_FULLSCREEN_WINDOW,
                                    !(al_get_display_flags(control->disp) & ALLEGRO_FULLSCREEN_WINDOW)
                );
                control->fullscreen = bool(al_get_display_flags(control->disp) & ALLEGRO_FULLSCREEN_WINDOW);
                al_resize_display(control->disp,control->res.getWidth(),control->res.getHeight());
                if(control->fullscreen) menu.getActiveElement()->setOptSetting(": TAK");
                else menu.getActiveElement()->setOptSetting(": NIE");
            }else
            if(!control->fullscreen) {
                if (menu.getActiveElement()->getName() == "800x600") {
                    control->res.changeResolution(RES_800X600, control->disp);
                }
                if (menu.getActiveElement()->getName() == "1024x768") {
                    control->res.changeResolution(RES_1024X768, control->disp);
                }
                if (menu.getActiveElement()->getName() == "1280x720") {
                    control->res.changeResolution(RES_1280X720, control->disp);
                }
                if (menu.getActiveElement()->getName() == "1366x768") {
                    control->res.changeResolution(RES_1366X768, control->disp);
                }
                if (menu.getActiveElement()->getName() == "1600x900") {
                    control->res.changeResolution(RES_1600X900, control->disp);
                }
                if (menu.getActiveElement()->getName() == "1920x1080") {
                    control->res.changeResolution(RES_1920X1080, control->disp);
                }
            }
            else{
                if(menu.getMenuType() == MT_RES){
                    al_resize_display(control->disp,
                                      menu.getActiveElement()->getDisplayMode()->width,
                                      menu.getActiveElement()->getDisplayMode()->height
                    );
                }
            }
            control->enter = false;
        }
        al_flip_display();
    }
    al_destroy_font(titleFont);
    ev->menu = nullptr;
}

#endif //TETRIS_MENU_H
