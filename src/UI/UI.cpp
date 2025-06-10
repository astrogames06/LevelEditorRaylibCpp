#include "UI.hpp"

#include "../Game/Game.hpp"
#include "../Systems/WorldEditor.hpp"

#include <raygui.h>
#include <iostream>

#ifdef PLATFORM_WEB
    #include <emscripten/emscripten.h>
#endif

#include "../Data/Data.hpp"

extern Game game;
int mode_icon = 23;

int GuiButtonRounded(Rectangle bounds, const char *text, float roundness, int segments, std::vector<Rectangle>& v);
void DrawUI()
{
    if (game.scene == SCENE::EDITOR)
    {
        if (GuiButtonRounded({(float)game.WIDTH-110, 10, 100, 45}, "PLAY!", 5.f, 20.f, game.UI_recs))
        {
            game.scene = SCENE::GAME;
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

        if (GuiButtonRounded({285, 10, 45, 45}, "#221#", 5.f, 5.f, game.UI_recs))
        {
            game.mode = SPIKES;
            mode_icon = 221;
        }
        DrawText(std::to_string(game.entities.size()).c_str(), 20, 20, 20, BLACK);
        if (GuiButtonRounded({(float)10, (float)game.HEIGHT-55, 100, 45}, "LOAD GAME!", 5.f, 20.f, game.UI_recs))
        {
            #ifdef PLATFORM_WEB
                emscripten_run_script("document.getElementById('jsonFileInput').click();");
            #endif
        }
        if (GuiButtonRounded({(float)game.WIDTH-110, (float)game.HEIGHT-55, 100, 45}, "SAVE GAME!", 5.f, 20.f, game.UI_recs))
        {
            SaveDataJSON();
        }
        GuiDrawIcon(mode_icon, GetMouseX()-5, GetMouseY()-10, 1, DARKGRAY);
    }

    else if (game.scene == SCENE::GAME)
    {
        if (GuiButtonRounded({(float)game.WIDTH-110, 10, 100, 45}, "STOP!", 5.f, 20.f, game.UI_recs))
        {
            game.Reset();
            return;
        }
    }
    else if (game.scene == SCENE::DEAD)
    {
        DrawText("YOU HAVE DIED!", game.WIDTH/2-MeasureText("YOU HAVE DIED!", 40)/2, 150, 40, BLACK);
        if (GuiButton({(float)game.WIDTH/2-100/2, 250, 150, 95}, "GO BACK TO EDITOR!")) game.Reset();
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