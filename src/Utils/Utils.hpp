#ifndef UTILS_H
#define UTILS_H

#include <raylib.h>

#include "../Game/Game.hpp"
#include "../Entity/Entity.hpp"

extern Game game;

bool IsOverEntity()
{
    for (std::unique_ptr<Entity>& entity : game.entities)
    {
        if (CheckCollisionPointRec(GetMousePosition(), {
            (float)entity->x, (float)entity->y, game.CELL_SIZE, game.CELL_SIZE
        }))
            return true;
    }
    return false;
}

bool IsOverEntityDragging(Entity* dragging)
{
    Rectangle dragRect = {
        game.world_mouse_pos.x,
        game.world_mouse_pos.y,
        game.CELL_SIZE,
        game.CELL_SIZE
    };

    for (const std::unique_ptr<Entity>& entity : game.entities)
    {
        if (entity.get() == dragging)
            continue;

        Rectangle otherRect = {
            (float)entity->x,
            (float)entity->y,
            game.CELL_SIZE,
            game.CELL_SIZE
        };

        if (CheckCollisionRecs(dragRect, otherRect))
            return true;
    }
    return false;
}


#endif