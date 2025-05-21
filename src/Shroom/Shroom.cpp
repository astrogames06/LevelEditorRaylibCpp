#include "Shroom.hpp"

#include <iostream>

#include "../Game/Game.hpp"
#include "../Enemy/Enemy.hpp"

extern Game game;

void Shroom::Init()
{
    texture = LoadTexture("assets/mushroom.png");
}

void Shroom::Update()
{
    for (std::unique_ptr<Entity>& entity : game.entities)
    {
        if (CheckCollisionRecs(
            {(float)x, (float)y, game.CELL_SIZE, game.CELL_SIZE},
            {
                (float)entity->x,
                (float)entity->y,
                game.CELL_SIZE, game.CELL_SIZE
            }
        ))
        {
            if (Player* player = dynamic_cast<Player*>(entity.get()))
            {
                if (!player->isOnGround &&
                    player->x + game.CELL_SIZE > x &&
                    player->velocity.y > 0)
                {
                    player->velocity.y = 0;
                    player->velocity.y -= bounciness;
                }
            }
            else if (Enemy* enemy = dynamic_cast<Enemy*>(entity.get()))
            {
                if (!enemy->isOnGround &&
                    enemy->x + game.CELL_SIZE > x &&
                    enemy->velocity.y > 0)
                {
                    enemy->velocity.y = 0;
                    enemy->velocity.y -= bounciness;
                }
            }
        }
    }
}

void Shroom::Draw()
{
    DrawTexture(texture, x, y, WHITE);
}

void Shroom::Reset()
{

}