#ifndef TETRIS_GAMEOBJECTS_H
#define TETRIS_GAMEOBJECTS_H

enum objectType{
    OT_GRID,
    OT_PLAYABLE
};

enum gameGridType{
    GGT_NULL,
    GGT_FRAME_WE,
    GGT_FRAME_NS,
    GGT_FRAME_SE,
    GGT_GFRAME_SW,
    GGT_FRAME_NE,
    GGT_FRAME_NW,
    GGT_OBJECT
};

enum GameObjectShape{
    GOBJECT_SQUARE,
    GOBJECT_LINE,
    GOBJECT_T,
    GOBJECT_L,
    GOBJECT_J,
    GOBJECT_Z,
    GOBJECT_S
};

class gameObject{
    unsigned int id;
    objectType type;
public:
    gameObject(unsigned int id_, objectType type_):id(id_),type(type_){}

};

class gameGrid{
    std::vector<std::vector<int>> grid;
public:
    explicit gameGrid(std::vector<std::vector<int>> grid_): grid(grid_){

    }

};


#endif //TETRIS_GAMEOBJECTS_H
