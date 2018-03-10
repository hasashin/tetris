#ifndef TETRIS_OBJECTS_H
#define TETRIS_OBJECTS_H

#include <allegro5/allegro.h>
#include <allegro5/display.h>
#include <allegro5/keyboard.h>
#include <vector>
#include <allegro5/allegro_ttf.h>

enum programState {
    PS_MENU,
    PS_INGAME,
    PS_PAUSE,
    PS_GAMEOVER
};
enum menuToggleType {
    MTT_NONE,
    MTT_DOWN,
    MTT_UP
};
enum menuType {
    MT_MAIN,
    MT_SETTINGS,
    MT_RES,
    MT_FULLSCRN,
    MT_MUSIC
};
enum resType {
    RES_800X600,
    RES_1024X768,
    RES_1280X720,
    RES_1366X768,
    RES_1600X900,
    RES_1920X1080
};

class rozdzielczosc {
    std::vector<ALLEGRO_DISPLAY_MODE*> fullscreenDispModes;
    int Width = 800, Height = 600,x=0,y=0;
public:
    rozdzielczosc(){
        for(int i=0;i<al_get_num_display_modes();i++){
            fullscreenDispModes.push_back(al_get_display_mode(i,new ALLEGRO_DISPLAY_MODE));
        }
    }
    void changeResolution(const resType& type,ALLEGRO_DISPLAY* disp) {
        int lastW=Width,lastH=Height;
        switch (type) {
            case RES_800X600:
                Width = 800;
                Height = 600;
                break;
            case RES_1024X768:
                Width = 1024;
                Height = 768;
                break;
            case RES_1280X720:
                Width = 1280;
                Height = 720;
                break;
            case RES_1366X768:
                Width = 1366;
                Height = 768;
                break;
            case RES_1600X900:
                Width = 1600;
                Height = 900;
                break;
            case RES_1920X1080:
                Width = 1920;
                Height = 1080;
                break;
            default:
                break;
        }
        al_resize_display(disp,Width,Height);
        //TODO: set proper window position according to resolution of the screen
        al_get_window_position(disp,&x,&y);
        al_set_window_position(disp,x+(lastW-Width)/2,y+(lastH-Height)/2);

    }

    int getWidth() {
        return Width;
    }

    int getHeight() {
        return Height;
    }
    std::vector<ALLEGRO_DISPLAY_MODE*> getFullscreenDisplayModes(){
        return fullscreenDispModes;
    }
};

struct sterowanie {
    bool close = false;
    programState state = PS_MENU;
    menuToggleType menutoggle = MTT_NONE;
    bool enter = false;
    rozdzielczosc res;
    menuType menutype = MT_MAIN;
    bool fullscreen=false;
    ALLEGRO_DISPLAY* disp = al_get_current_display();
};

struct EVENT_HANDLER {
    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_EVENT *event;
    sterowanie *control;
    ALLEGRO_KEYBOARD_STATE *keyboard;

    EVENT_HANDLER(
            ALLEGRO_EVENT_QUEUE *queue_,
            ALLEGRO_EVENT *event_,
            sterowanie *control_,
            ALLEGRO_KEYBOARD_STATE *keyboard_
    ) : queue(queue_), event(event_), control(control_), keyboard(keyboard_) {}


};

class MenuElement {
    const std::string Name, Value;
    bool Active;
public:
    MenuElement(std::string Name_, std::string Value_) : Name(Name_), Value(Value_) {
        Active = false;
    }

    void toggleActiveFlag() {
        Active = !Active;
    }

    bool isActive() {
        return Active;
    };

    std::string getName() {
        return Name;
    }

    std::string getValue() {
        return Value;
    }
};

class Menu {
protected:
    std::vector<MenuElement> elementsList;
    std::vector<MenuElement>::iterator activeElement = elementsList.begin();
    sterowanie *control;
public:
    explicit Menu(menuType type, sterowanie *control_) : control(control_) {
        elementsList.clear();
        changeMenuType(type);
    }

    void changeMenuType(menuType type) {
        elementsList.clear();
        switch (type) {
            case MT_MAIN:
                elementsList.push_back(MenuElement("newgame", "Nowa Gra"));
                elementsList.push_back(MenuElement("settings", "Ustawienia"));
                elementsList.push_back(MenuElement("close", "Zakończ"));
                setActiveElement(0);
                break;
            case MT_SETTINGS:
                elementsList.push_back(MenuElement("music", "Ustawienia muzyki"));
                elementsList.push_back(MenuElement("resolution", "Rozdzielczość ekranu"));
                elementsList.push_back(MenuElement("fullscreen", "Pełny ekran"));
                elementsList.push_back(MenuElement("backfromsettings", "Wróć"));
                setActiveElement(0);
                break;
            case MT_RES: {
                if(control->fullscreen){
                    int active;
                    for(int i = (int)control->res.getFullscreenDisplayModes().size()-1;i<=0;i--){
                        std::string ss;
                        ss = control->res.getFullscreenDisplayModes()[i]->width;
                        ss += "x";
                        ss += control->res.getFullscreenDisplayModes()[i]->height;
                        elementsList.push_back(MenuElement(ss,ss));
                        if(al_get_display_width(control->disp) == control->res.getFullscreenDisplayModes()[i]->width
                                && al_get_display_height(control->disp) == control->res.getFullscreenDisplayModes()[i]->height){
                            setActiveElement(i);
                        }
                    }
                    elementsList.push_back(MenuElement("backfromres","Wróć"));
                }
                else {
                    elementsList.emplace_back(MenuElement("800x600", "800x600"));
                    elementsList.push_back(MenuElement("1024x768", "1024x768"));
                    elementsList.push_back(MenuElement("1280x720", "1280x720"));
                    elementsList.push_back(MenuElement("1366x768", "1366x768"));
                    elementsList.push_back(MenuElement("1600x900", "1600x900"));
                    elementsList.push_back(MenuElement("1920x1080", "1920x1080"));
                    elementsList.push_back(MenuElement("backfromres", "Wróć"));
                    int i = 0;
                    for (auto &elem:elementsList) {
                        if (std::stoi(elem.getName().substr(0, elem.getName().find('x'))) == control->res.getWidth()
                                && std::stoi(elem.getName().substr(elem.getName().find('x')+1)) == control->res.getHeight()) {
                            setActiveElement(i);
                            break;
                        }
                        i++;
                    }
                }
                break;
            }
            default:
                break;
            case MT_FULLSCRN:break;
            case MT_MUSIC:break;
        }
    }

    MenuElement *getElement(int i) {
        if (i <= elementsList.size()) {
            return &elementsList[i];
        }
        return nullptr;
    }

    void displayMenu() {
        auto menuFnt = al_load_ttf_font("fonts/menu.ttf", int(0.05 * control->res.getHeight()), 0);
        if (!menuFnt) menuFnt = al_create_builtin_font();
        int i = 0;
        for (auto elem : elementsList) {
            al_draw_text(
                    menuFnt,
                    (elem.isActive() ? al_map_rgb(255, 255, 255) : al_map_rgb(155, 155, 155)),
                    0.3f*control->res.getWidth(),
                    300 + i,
                    0,
                    elem.getValue().data()
            );
            i += 30;
        }
        al_destroy_font(menuFnt);
    }

    int getElementsCount() {
        return (int) elementsList.size();
    }

    void setActiveElement(int i) {
        activeElement = elementsList.begin() + i;
        for (auto elem : elementsList) {
            if (elem.isActive()) elem.toggleActiveFlag();
        }
        (*activeElement).toggleActiveFlag();
    }

    void changeActiveElement(menuToggleType *type) {
        if ((*type) == MTT_UP) {
            if (activeElement != elementsList.begin()) {
                activeElement->toggleActiveFlag();
                activeElement = activeElement - 1;
                activeElement->toggleActiveFlag();
            }
        }
        if ((*type) == MTT_DOWN) {
            if (activeElement != elementsList.end() - 1) {
                activeElement->toggleActiveFlag();
                activeElement = activeElement + 1;
                activeElement->toggleActiveFlag();
            }
        }
        (*type) = MTT_NONE;

    }

    std::vector<MenuElement>::iterator getActiveElement() {
        return activeElement;
    }
};

#endif //TETRIS_OBJECTS_H
