#include "Game.hpp"

#include <iostream>
#include <algorithm>
#include <raygui.h>

#include "../UI/UI.hpp"
#include "../Block/Block.hpp"
#include "../Systems/WorldEditor.hpp"
#include "../Enemy/Enemy.hpp"
#include "../Systems/MainSystems.hpp"

void Game::Init()
{
    GuiLoadIcons("assets/iconset.rgi", false);

    std::unique_ptr<Player> player = std::make_unique<Player>();
    player->origin_pos = {5*CELL_SIZE, 5*CELL_SIZE};
    player->x = 5*CELL_SIZE;
    player->y = 5*CELL_SIZE;
    player->Init();
    entities.push_back(std::move(player));

    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    for (int x = 0; x < WIDTH/CELL_SIZE; x++)
    {
        entities.push_back(std::make_unique<Block>(x * CELL_SIZE, HEIGHT - CELL_SIZE));
    }

    for (int x = 0; x < WIDTH/CELL_SIZE; x++)
    {
        for (int y = 0; y < HEIGHT/CELL_SIZE; y++)
        {
            cells.push_back(Rectangle{x*CELL_SIZE, y*CELL_SIZE, CELL_SIZE, CELL_SIZE});
        }
    }
}

void Game::Update()
{
    if (!running)
    {
        RunMouseControl();
        RunCameraControl();

        // VERY IMPORTANT FOR PLACING ENTITIES SYSTEMS
        RunWorldEditorSystem();
    }
    else if (running)
    {
        for (std::unique_ptr<Entity>& entity : entities)
        {
            if (entity && entity->alive) entity->Update();
        }
    }
    // Remove it if Entity->alive = false;
    game.entities.erase(
        std::remove_if(
            game.entities.begin(),
            game.entities.end(),
            [](const std::unique_ptr<Entity>& e) { return e->remove; }
        ),
        game.entities.end()
    );
}

extern int mode_icon;
void Game::Draw()
{
    // std::cout << mode << '\n';
    // std::cout << GetEntitiesOfType<Enemy>().size() << '\n';
    
    BeginDrawing();
    ClearBackground(WHITE);
    BeginMode2D(camera);

    for (std::unique_ptr<Entity>& entity : entities)
    {
        if (entity && entity->alive) entity->Draw();
    }

    if (!running)
    {
        for (Rectangle& cell : cells)
        {
            DrawRectangleLinesEx(cell, 1.f, GRAY);
        }

        DrawRectangleV(world_mouse_pos, {CELL_SIZE, CELL_SIZE}, Color{0, 0, 0, 50});
    }
    EndMode2D();
    DrawUI();

    if (!running)
        GuiDrawIcon(mode_icon, GetMouseX()-5, GetMouseY()-10, 1, DARKGRAY);

    EndDrawing();
}

void Game::Reset()
{
    running = false;

    for (std::unique_ptr<Entity>& entity : entities)
    {
        entity->Reset();
    }

    cells.clear();
    for (int x = 0; x < WIDTH/CELL_SIZE; x++)
    {
        for (int y = 0; y < HEIGHT/CELL_SIZE; y++)
        {
            cells.push_back({x*CELL_SIZE, y*CELL_SIZE, CELL_SIZE, CELL_SIZE});
        }
    }

    camera = { 0 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}