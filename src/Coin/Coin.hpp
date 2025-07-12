#ifndef COIN_H
#define COIN_H

#include <raylib.h>
#include "../Game/Game.hpp"
#include "../Entity/Entity.hpp"

#include <iostream>

extern Game game;

class Coin : public Entity
{
public:
    Coin(float x, float y)
    {
        this->type = ENTITY_TYPE::COIN_TYPE;
        this->x = x;
        this->y = y;
        texture = LoadTexture("assets/coin.png");
        Init();
    }

    void Update() override
    {
        Player* player = game.GetEntityOfType<Player>();

        if (CheckCollisionRecs(
            {(float)player->x, (float)player->y, game.CELL_SIZE, game.CELL_SIZE},
            {(float)x, (float)y, (float)texture.width, (float)texture.height}
        ))
        {
            player->coins++;
            Kill();
        }
    }

    void Draw() override
    {
        DrawTexture(texture, x, y, WHITE);
        // DrawRectangleLines(x, y, texture.width, texture.height, BLUE);

        // Player* player = game.GetEntityOfType<Player>();
        // DrawRectangleLines((float)player->x, (float)player->y, game.CELL_SIZE, game.CELL_SIZE, ORANGE);
    }
};

#endif
