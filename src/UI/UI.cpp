#include "UI.hpp"

#include "../Game/Game.hpp"
#include "../Systems/WorldEditor.hpp"

#include <raygui.h>
#include <iostream>

extern Game game;
int mode_icon = 23;

int GuiButtonRounded(Rectangle bounds, const char *text, float roundness, int segments, std::vector<Rectangle>& v);
void DrawUI()
{
    if (!game.running)
    {
        if (GuiButtonRounded({(float)game.WIDTH-110, 10, 100, 45}, "PLAY!", 5.f, 20.f, game.UI_recs))
        {
            game.running = true;
            return;
        }

        if (GuiButtonRounded({10, 10, 45, 45}, "#23#", 5.f, 5.f, game.UI_recs))
        {
            game.mode = BLOCK;
            mode_icon = 23;
        }

        if (GuiButtonRounded({65, 10, 45, 45}, "#28#", 5.f, 5.f, game.UI_recs))
        {
            game.mode = ERASE;
            mode_icon = 28;
        }

        if (GuiButtonRounded({120, 10, 45, 45}, "#21#", 5.f, 5.f, game.UI_recs))
        {
            game.mode = MOVE;
            mode_icon = 21;
        }

        if (GuiButtonRounded({175, 10, 45, 45}, "#152#", 5.f, 5.f, game.UI_recs))
        {
            game.mode = ENEMY;
            mode_icon = 152;
        }

        if (GuiButtonRounded({230, 10, 45, 45}, "#220#", 5.f, 5.f, game.UI_recs))
        {
            game.mode = SHROOM;
            mode_icon = 220;
        }
    }

    if (game.running)
    {
        if (GuiButtonRounded({(float)game.WIDTH-110, 10, 100, 45}, "STOP!", 5.f, 20.f, game.UI_recs))
        {
            game.Reset();
            return;
        }
    }
    DrawFPS(20, game.HEIGHT-20);
}
bool IsOverUI()
{
    for (Rectangle& r : game.UI_recs)
    {
        if (CheckCollisionPointRec(GetMousePosition(), r))
            return true;
    }
    return false;
}