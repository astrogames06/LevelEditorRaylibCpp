#include "Spikes.hpp"

#include "../Game/Game.hpp"

extern Game game;

Rectangle spikes_hit_box;
void Spikes::Init()
{
    texture = LoadTexture("assets/spikes.png");
    spikes_hit_box = {(float)x, (float)(y + texture.height - 15), (float)texture.width, 15};
}

void Spikes::Update()
{
    Player* player = game.GetEntityOfType<Player>();

    if (CheckCollisionRecs(
        {(float)player->x, (float)player->y, game.CELL_SIZE, game.CELL_SIZE},
        spikes_hit_box
    ))
    {
        player->Kill();
    }
}

void Spikes::Draw()
{
    DrawTexture(texture, x, y, WHITE);
    // DrawRectangleLinesEx(spikes_hit_box, 1.f, GREEN);
}