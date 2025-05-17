#include "Game.hpp"

#include <iostream>

#include "../UI/UI.hpp"

void Game::Init()
{
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
    //std::cout << (mode == MOVE) << '\n';
    if (IsKeyPressed(KEY_E)) running = !running;
    if (!running)
    {
        world_mouse_pos = GetMousePosition();

        for (Rectangle& cell : cells)
        {
            if (CheckCollisionPointRec(world_mouse_pos, cell)) world_mouse_pos = {cell.x, cell.y};
        }

        int block_index = -1;
        bool block_there = false;
        for (int i = 0; i < blocks.size(); i++)
        {
            Rectangle& block = blocks[i];
            if (CheckCollisionPointRec(world_mouse_pos, block))
            {
                block_there = true;
                block_index = i;
                break;
            }
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (mode == BLOCK)
            {
                if (!block_there)
                {
                    blocks.push_back({world_mouse_pos.x, world_mouse_pos.y, CELL_SIZE, CELL_SIZE});
                }
                else
                {
                    blocks.erase(blocks.begin() + block_index);
                }
            }
        }
    }
    if (running)
    {
        camera.target = {(float)GetPlayer()->x, (float)GetPlayer()->y};
        camera.offset = { WIDTH / 2.0f, HEIGHT / 2.0f };
    }
    for (std::unique_ptr<Entity>& entity : entities)
    {
        entity->Update();
    }
}

void Game::Draw()
{
    BeginDrawing();
    ClearBackground(WHITE);
    BeginMode2D(camera);

    for (Rectangle& block : blocks)
    {
        DrawRectangleRec(block, RED);
    }

    for (std::unique_ptr<Entity>& entity : entities)
    {
        entity->Draw();
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

    EndDrawing();
}

void Game::Reset()
{
    running = false;

    GetPlayer()->rec.x = GetPlayer()->origin_pos.x;
    GetPlayer()->rec.y = GetPlayer()->origin_pos.y;
    GetPlayer()->x = GetPlayer()->origin_pos.x;
    GetPlayer()->y = GetPlayer()->origin_pos.y;

    camera = { 0 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}

Player* Game::GetPlayer()
{
    for (auto& entity : entities)
    {
        Player* player = dynamic_cast<Player*>(entity.get());
        if (player != nullptr)
            return player;
    }
    return nullptr; // not found
}