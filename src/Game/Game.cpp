#include "Game.hpp"

#include <iostream>

#include "../Player/Player.hpp"

void Game::Init()
{
    std::unique_ptr<Player> player = std::make_unique<Player>();
    player->x = 0;
    player->y = 0;
    player->Init();
    entities.push_back(std::move(player));

    for (int x = 0; x < WIDTH/CELL_SIZE; x++)
    {
        blocks.push_back({ x * CELL_SIZE, HEIGHT - CELL_SIZE, CELL_SIZE, CELL_SIZE });
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
    if (IsKeyPressed(KEY_E)) running = !running;
    if (!running)
    {
        world_mouse_pos = GetMousePosition();
        for (Rectangle& cell : cells)
        {
            if (CheckCollisionPointRec(world_mouse_pos, cell)) world_mouse_pos = {cell.x, cell.y};
        }
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            blocks.push_back({world_mouse_pos.x, world_mouse_pos.y, CELL_SIZE, CELL_SIZE});
        }
    }
    else if (running)
    {
        for (std::unique_ptr<Entity>& entity : entities)
        {
            entity->Update();
        }
    }
}

void Game::Draw()
{
    if (!running)
    {
        for (Rectangle& cell : cells)
        {
            DrawRectangleLinesEx(cell, 1.f, GRAY);
        }

        DrawRectangleV(world_mouse_pos, {CELL_SIZE, CELL_SIZE}, Color{0, 0, 0, 50});
    }

    for (Rectangle& block : blocks)
    {
        DrawRectangleRec(block, RED);
    }

    for (std::unique_ptr<Entity>& entity : entities)
    {
        entity->Draw();
    }
}
