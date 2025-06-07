#ifndef SCENES_H
#define SCENES_H

#include "Game.hpp"
#include "../Systems/MainSystems.hpp"
#include "../Systems/WorldEditor.hpp"

extern Game game;

void UpdateEditorScene()
{
    RunMouseControl();
    RunCameraControl();

    // VERY IMPORTANT FOR PLACING ENTITIES SYSTEMS
    RunWorldEditorSystem();
}
void DrawEditorScene()
{
    for (Rectangle& cell : game.cells)
    {
        DrawRectangleLinesEx(cell, 1.f, GRAY);
    }

    DrawRectangleV(game.world_mouse_pos, {game.CELL_SIZE, game.CELL_SIZE}, Color{0, 0, 0, 50});
}

void UpdateGameScene()
{
    Rectangle camera_rect = {
        game.camera.target.x - game.camera.offset.x / game.camera.zoom,
        game.camera.target.y - game.camera.offset.y / game.camera.zoom,
        game.WIDTH / game.camera.zoom,
        game.HEIGHT / game.camera.zoom
    };

    for (std::unique_ptr<Entity>& entity : game.entities)
    {
        Rectangle entity_rect = {(float)entity->x, (float)entity->y, (float)game.CELL_SIZE, (float)game.CELL_SIZE};
        if (entity && entity->alive && CheckCollisionRecs(camera_rect, entity_rect)) entity->Update();
    }
}

#endif