#include "WorldEditor.hpp"

#include <algorithm>

#include "../Game/Game.hpp"
#include "../UI/UI.hpp"
#include "../Block/Block.hpp"
#include "../Enemy/Enemy.hpp"
#include "../Utils/Utils.hpp"

extern Game game;

void BlockSystem()
{
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !IsOverUI() && !IsOverEntity())
    {
        game.entities.push_back(std::make_unique<Block>(game.world_mouse_pos.x, game.world_mouse_pos.y));
    }
}
void EraseSystem()
{
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !IsOverUI())
    {
        Entity* entity_to_remove = nullptr;
        for (std::unique_ptr<Entity>& entity : game.entities)
        {
            if (CheckCollisionPointRec(game.world_mouse_pos, {
                (float)entity->x, (float)entity->y, game.CELL_SIZE, game.CELL_SIZE
            }))
            {
                if (dynamic_cast<Player*>(entity.get()) == nullptr)
                    entity_to_remove = entity.get();
            }
        }

        if (entity_to_remove != nullptr)
        {
            game.entities.erase(std::remove_if(game.entities.begin(), game.entities.end(),
            [entity_to_remove](const std::unique_ptr<Entity>& ptr) {
                return ptr.get() == entity_to_remove;
            }), game.entities.end());
        }
    }
}
void MoveSystem()
{
    for (std::unique_ptr<Entity>& entity : game.entities)
    {
        Rectangle rect = {(float)entity->x, (float)entity->y, game.CELL_SIZE, game.CELL_SIZE};

        if (
            IsMouseButtonDown(MOUSE_BUTTON_LEFT)
            && CheckCollisionPointRec(game.world_mouse_pos, rect)
            && !game.dragging
        )
        {
            game.selected_entity = entity.get();
            game.dragging = true;
        }
    }

    if (game.selected_entity != nullptr && !IsOverUI() && !IsOverEntityDragging(game.selected_entity))
    {
        game.selected_entity->x = game.world_mouse_pos.x;
        game.selected_entity->y = game.world_mouse_pos.y;

        if (Block* block = dynamic_cast<Block*>(game.selected_entity))
        {
            block->rec.x = game.world_mouse_pos.x;
            block->rec.y = game.world_mouse_pos.y;
        }
        else if (Player* plr = dynamic_cast<Player*>(game.selected_entity))
        {
            plr->origin_pos = game.world_mouse_pos;
            plr->rec.x = game.world_mouse_pos.x;
            plr->rec.y = game.world_mouse_pos.y;
        }
        else if (Enemy* enemy = dynamic_cast<Enemy*>(game.selected_entity))
        {
            enemy->origin_pos = game.world_mouse_pos;
            enemy->x = game.world_mouse_pos.x;
            enemy->y = game.world_mouse_pos.y;
        }
    }

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && game.dragging)
    {
        game.dragging = false;
        game.selected_entity = nullptr;
    }
}

void EnemySystem()
{
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !IsOverUI() && !IsOverEntity())
    {
        // if (block_to_remove == nullptr)
        // {
        game.entities.push_back(std::make_unique<Enemy>(game.world_mouse_pos.x, game.world_mouse_pos.y));
        // }
        // else
        // {
        //     game.entities.erase(std::remove_if(game.entities.begin(), game.entities.end(),
        //     [block_to_remove](const std::unique_ptr<Entity>& ptr) {
        //         return ptr.get() == block_to_remove;
        //     }), game.entities.end());
        // }
    }
}

void RunWorldEditorSystem()
{
    switch (game.mode)
    {
    case BLOCK:
        BlockSystem();
        break;
    case ERASE:
        EraseSystem();
        break;
    case MOVE:
        MoveSystem();
        break;
    case ENEMY:
        EnemySystem();
        break;
    default:
        break;
    }
}