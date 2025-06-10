#include "WorldEditor.hpp"

#include <algorithm>

#include "../Game/Game.hpp"
#include "../UI/UI.hpp"
#include "../Block/Block.hpp"
#include "../Enemy/Enemy.hpp"
#include "../Utils/Utils.hpp"
#include "../Shroom/Shroom.hpp"
#include "../Spikes/Spikes.hpp"

extern Game game;

void BlockSystem()
{
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !IsOverUI())
    {
        if (GetEntityOver() != nullptr)
            GetEntityOver()->Delete();
        game.entities.push_back(std::make_unique<Block>(game.world_mouse_pos.x, game.world_mouse_pos.y));
    }
}
void EraseSystem()
{
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !IsOverUI())
    {
        // Makes sure that you arent trying to erase the player
        // Also makes sure the entity your trying to erase actually exists
        if (dynamic_cast<Player*>(GetEntityOver()) == nullptr && GetEntityOver() != nullptr)
            GetEntityOver()->Delete();
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
            block->x = game.world_mouse_pos.x;
            block->y = game.world_mouse_pos.y;
        }
        else if (Player* plr = dynamic_cast<Player*>(game.selected_entity))
        {
            plr->origin_pos = game.world_mouse_pos;
            plr->x = game.world_mouse_pos.x;
            plr->y = game.world_mouse_pos.y;
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
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !IsOverUI())
    {
        if (GetEntityOver() != nullptr)
            GetEntityOver()->Delete();
        game.entities.push_back(std::make_unique<Enemy>(game.world_mouse_pos.x, game.world_mouse_pos.y));
    }
}

void MushroomSystem()
{
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !IsOverUI())
    {
        if (GetEntityOver() != nullptr)
            GetEntityOver()->Delete();
        game.entities.push_back(std::make_unique<Shroom>(game.world_mouse_pos.x, game.world_mouse_pos.y));
    }
}

void SpikesSystem()
{
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !IsOverUI())
    {
        if (GetEntityOver() != nullptr)
            GetEntityOver()->Delete();
        game.entities.push_back(std::make_unique<Spikes>(game.world_mouse_pos.x, game.world_mouse_pos.y));
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
    case SHROOM:
        MushroomSystem();
        break;
    case SPIKES:
        SpikesSystem();
        break;
    default:
        break;
    }
}