#ifndef MAINSYSTEM_H
#define MAINSYSTEM_H

#include "../Game/Game.hpp"

#include <algorithm>

extern Game game;

void RunMouseControl()
{
    game.world_mouse_pos = GetScreenToWorld2D(GetMousePosition(), game.camera);
    for (Rectangle& cell : game.cells)
    {
        if (CheckCollisionPointRec(game.world_mouse_pos, cell)) game.world_mouse_pos = {cell.x, cell.y};
    }
}

void RunCameraFollowSystem()
{
    Player* player = game.GetEntityOfType<Player>();
    game.camera.target = {(float)round(player->x), (float)round(player->y)};
    game.camera.offset = {(float)round(game.WIDTH / 2.0f), (float)round(game.HEIGHT / 2.0f)};
}

void RunCameraControl()
{
    if ((IsKeyPressed(KEY_W) || IsKeyDown(KEY_UP)))
    {
        game.camera.target.y -= game.CELL_SIZE;
        std::for_each(game.cells.begin(), game.cells.end(), [](Rectangle& cell) {
            cell.y -= game.CELL_SIZE;
        });
    }
    if ((IsKeyPressed(KEY_A) || IsKeyDown(KEY_LEFT)))
    {
        game.camera.target.x -= game.CELL_SIZE;
        std::for_each(game.cells.begin(), game.cells.end(), [](Rectangle& cell) {
            cell.x -= game.CELL_SIZE;
        });
    }
    if ((IsKeyPressed(KEY_S) || IsKeyDown(KEY_DOWN))) {
        game.camera.target.y += game.CELL_SIZE;
        std::for_each(game.cells.begin(), game.cells.end(), [](Rectangle& cell) {
            cell.y += game.CELL_SIZE;
        });
    }
    if ((IsKeyPressed(KEY_D) || IsKeyDown(KEY_RIGHT)))
    {
        game.camera.target.x += game.CELL_SIZE;
        std::for_each(game.cells.begin(), game.cells.end(), [](Rectangle& cell) {
            cell.x += game.CELL_SIZE;
        });
    }
}

#endif