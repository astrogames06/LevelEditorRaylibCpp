#include "UI.hpp"

#include "../Game/Game.hpp"

#include <raygui.h>
#include <iostream>

extern Game game;

int GuiButtonRounded(Rectangle bounds, const char *text, float roundness, int segments);
void DrawUI()
{
    if (!game.running)
    {
        if (GuiButtonRounded({(float)game.WIDTH-110, 10, 100, 45}, "PLAY!", 5.f, 20.f))
        {
            game.running = true;
            return;
        }

        if (GuiButtonRounded({10, 10, 45, 45}, "#23#", 5.f, 5.f))
        {
            game.mode = BLOCK;
        }

        if (GuiButtonRounded({65, 10, 45, 45}, "#21#", 5.f, 5.f))
        {
            game.mode = MOVE;
        }
    }

    if (game.running)
    {
        if (GuiButtonRounded({(float)game.WIDTH-110, 10, 100, 45}, "STOP!", 5.f, 20.f))
        {
            game.Reset();
            return;
        }
    }
}