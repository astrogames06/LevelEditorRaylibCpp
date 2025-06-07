#include "Spikes.hpp"

void Spikes::Init()
{
    texture = LoadTexture("assets/spikes.png");
    SetTextureFilter(texture, TEXTURE_FILTER_POINT);
}

void Spikes::Update()
{
    ;
}

void Spikes::Draw()
{
    DrawTexture(texture, x, y, WHITE);
}