#ifndef GAME_H
#define GAME_H

#include <vector>
#include <raylib.h>
#include <memory>
#include <string>

#include "../Entity/Entity.hpp"

class Game
{
public:
    const int WIDTH = 875;
    const int HEIGHT = 455;
    const std::string TITLE = "Level Builder!";
    bool running = false;

    Vector2 world_mouse_pos;
    float CELL_SIZE = 35.f;
    std::vector<Rectangle> cells;
    
    std::vector<std::unique_ptr<Entity>> entities;
    std::vector<Rectangle> blocks;

    void Init();
    void Update();
    void Draw();
};

#endif