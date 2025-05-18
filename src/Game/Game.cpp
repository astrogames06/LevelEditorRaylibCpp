#include "Game.hpp"

#include <iostream>
#include <algorithm>

#include "../UI/UI.hpp"

#include "../Block/Block.hpp"

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
        world_mouse_pos = GetScreenToWorld2D(GetMousePosition(), camera);

        if ((IsKeyPressed(KEY_W) || IsKeyDown(KEY_UP)))
        {
            camera.target.y -= CELL_SIZE;
            std::for_each(cells.begin(), cells.end(), [this](Rectangle& cell) {
                cell.y -= CELL_SIZE;
            });
        }
        if ((IsKeyPressed(KEY_A) || IsKeyDown(KEY_LEFT)))
        {
            camera.target.x -= CELL_SIZE;
            std::for_each(cells.begin(), cells.end(), [this](Rectangle& cell) {
                cell.x -= CELL_SIZE;
            });
        }
        if ((IsKeyPressed(KEY_S) || IsKeyDown(KEY_DOWN))) {
            camera.target.y += CELL_SIZE;
            std::for_each(cells.begin(), cells.end(), [this](Rectangle& cell) {
                cell.y += CELL_SIZE;
            });
        }
        if ((IsKeyPressed(KEY_D) || IsKeyDown(KEY_RIGHT)))
        {
            camera.target.x += CELL_SIZE;
            std::for_each(cells.begin(), cells.end(), [this](Rectangle& cell) {
                cell.x += CELL_SIZE;
            });
        }

        for (Rectangle& cell : cells)
        {
            if (CheckCollisionPointRec(world_mouse_pos, cell)) world_mouse_pos = {cell.x, cell.y};
        }

        Entity* block_to_remove = nullptr;
        for (int i = 0; i < GetEntitiesOfType<Block>().size(); i++)
        {
            if (CheckCollisionPointRec(world_mouse_pos, GetEntitiesOfType<Block>()[i]->rec))
            {
                block_to_remove = GetEntitiesOfType<Block>()[i];
                break;
            }
        }

        if (game.mode == MOVE)
        {
            for (std::unique_ptr<Entity>& entity : entities)
            {
                Rectangle rect = {(float)entity->x, (float)entity->y, CELL_SIZE, CELL_SIZE};

                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(world_mouse_pos, rect))
                {
                    selected_entity = entity.get();
                    dragging = true;
                }
            }

            if (selected_entity != nullptr)
            {
                selected_entity->x = world_mouse_pos.x;
                selected_entity->y = world_mouse_pos.y;

                if (Block* block = dynamic_cast<Block*>(selected_entity))
                {
                    block->rec.x = world_mouse_pos.x;
                    block->rec.y = world_mouse_pos.y;
                }
                else if (Player* plr = dynamic_cast<Player*>(selected_entity))
                {
                    plr->origin_pos = world_mouse_pos;
                    plr->rec.x = world_mouse_pos.x;
                    plr->rec.y = world_mouse_pos.y;
                }
            }

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && dragging)
            {
                dragging = false;
                selected_entity = nullptr;
            }
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (mode == BLOCK)
            {
                if (block_to_remove == nullptr)
                {
                    entities.push_back(std::make_unique<Block>(world_mouse_pos.x, world_mouse_pos.y));
                }
                else
                {
                    entities.erase(std::remove_if(entities.begin(), entities.end(),
                    [block_to_remove](const std::unique_ptr<Entity>& ptr) {
                        return ptr.get() == block_to_remove;
                    }), entities.end());
                }
            }
        }
    }
    if (running)
    {
        camera.target = {(float)GetEntityOfType<Player>()->x, (float)GetEntityOfType<Player>()->y};
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

    GetEntityOfType<Player>()->rec.x = GetEntityOfType<Player>()->origin_pos.x;
    GetEntityOfType<Player>()->rec.y = GetEntityOfType<Player>()->origin_pos.y;
    GetEntityOfType<Player>()->x = GetEntityOfType<Player>()->origin_pos.x;
    GetEntityOfType<Player>()->y = GetEntityOfType<Player>()->origin_pos.y;

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