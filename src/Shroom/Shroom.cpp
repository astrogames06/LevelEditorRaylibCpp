#include "Shroom.hpp"

#include <iostream>

#include "../Game/Game.hpp"

extern Game game;

void Shroom::Init()
{
    texture = LoadTexture("assets/mushroom.png");
}

void Shroom::Update()
{
    if (CheckCollisionRecs(
        {(float)x, (float)y, game.CELL_SIZE, game.CELL_SIZE},
        {
            (float)game.GetEntityOfType<Player>()->rec.x,
            (float)game.GetEntityOfType<Player>()->rec.y,
            game.CELL_SIZE, game.CELL_SIZE
        }
    ))
    {
        if (!game.GetEntityOfType<Player>()->isOnGround && 
            game.GetEntityOfType<Player>()->x+game.CELL_SIZE > x
        )
        {
            game.GetEntityOfType<Player>()->velocity.y = 0;
            game.GetEntityOfType<Player>()->velocity.y -= bounciness;
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