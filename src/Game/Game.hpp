#ifndef GAME_H
#define GAME_H

#include <vector>
#include <raylib.h>
#include <memory>
#include <string>

#include "../Entity/Entity.hpp"
#include "../Player/Player.hpp"

enum EDIT_MODE
{
    BLOCK,
    ERASE,
    MOVE,
    ENEMY,
    SHROOM,
    SPIKES
};

enum SCENE
{
    EDITOR,
    GAME,
    DEAD
};

class Game
{
public:
    const int WIDTH = 875;
    const int HEIGHT = 455;
    const std::string TITLE = "Level Builder!";
    SCENE scene = SCENE::EDITOR;

    Camera2D camera;
    std::vector<Rectangle> UI_recs;

    EDIT_MODE mode = BLOCK;

    Vector2 world_mouse_pos;
    float CELL_SIZE = 35.f;
    std::vector<Rectangle> cells;
    
    std::vector<std::unique_ptr<Entity>> entities;
    template <typename T>
    T* GetEntityOfType();

    template <typename T>
    std::vector<T*> GetEntitiesOfType();

    Entity* selected_entity = nullptr;
    bool dragging = false;

    void Init();
    void Update();
    void Draw();

    void Reset();
};

template <typename T>
T* Game::GetEntityOfType()
{
    for (auto& entity : entities)
    {
        T* result = dynamic_cast<T*>(entity.get());
        if (result != nullptr)
            return result;
    }
    return nullptr;
}

template <typename T>
std::vector<T*> Game::GetEntitiesOfType()
{
    std::vector<T*> results;
    for (auto& entity : entities)
    {
        T* result = dynamic_cast<T*>(entity.get());
        if (result != nullptr)
            results.push_back(result);
    }
    return results;
}

#endif