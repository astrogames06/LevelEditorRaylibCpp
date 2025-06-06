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
    for (std::unique_ptr<Entity>& entity : game.entities)
    {
        if (entity && entity->alive) entity->Update();
    }
}

#endif