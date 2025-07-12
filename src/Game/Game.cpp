#include "Game.hpp"

#include <iostream>
#include <algorithm>
#include <raygui.h>

#include "../UI/UI.hpp"
#include "../Block/Block.hpp"
#include "../Systems/WorldEditor.hpp"
#include "../Enemy/Enemy.hpp"
#include "../Systems/MainSystems.hpp"
#include "Scenes.hpp"

void Game::Init()
{
    GuiLoadIcons("assets/iconset.rgi", false);

    std::unique_ptr<Player> player = std::make_unique<Player>();
    player->origin_pos = {5*CELL_SIZE, 5*CELL_SIZE};
    player->x = 5*CELL_SIZE;
    player->y = 5*CELL_SIZE;
    player->Init();
    entities.push_back(std::move(player));

    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    for (int x = 0; x < WIDTH/CELL_SIZE; x++)
    {
        entities.push_back(std::make_unique<Block>(x * CELL_SIZE, HEIGHT - CELL_SIZE));
    }

    for (int x = camera.target.x; x < WIDTH/CELL_SIZE; x++)
    {
        for (int y = camera.target.y; y < HEIGHT/CELL_SIZE; y++)
        {
            cells.push_back(Rectangle{x*CELL_SIZE, y*CELL_SIZE, CELL_SIZE, CELL_SIZE});
        }
    }
}
    
void Game::Update()
{
    if (scene == SCENE::EDITOR)
    {
        UpdateEditorScene();
    }
    else if (scene == SCENE::GAME)
    {
        RunCameraFollowSystem();
        UpdateGameScene();
    }
    
    // Remove it if Entity->remove = true;
    game.entities.erase(
        std::remove_if(
            game.entities.begin(),
            game.entities.end(),
            [](const std::unique_ptr<Entity>& e) { return e->remove; }
        ),
        game.entities.end()
    );
}

extern int mode_icon;
void Game::Draw()
{
    // std::cout << mode << '\n';
    // std::cout << GetEntitiesOfType<Enemy>().size() << '\n';
    
    BeginDrawing();
    ClearBackground(WHITE);
    BeginMode2D(camera);

    if (scene == SCENE::EDITOR || scene == SCENE::GAME)
    {
        for (std::unique_ptr<Entity>& entity : entities)
        {
            if (entity && entity->alive) entity->Draw();
        }
    }

    if (scene == SCENE::EDITOR)
    {
        DrawEditorScene();
    }

    EndMode2D();
    DrawUI();

    EndDrawing();
}

void Game::Reset()
{
    scene = SCENE::EDITOR;

    for (std::unique_ptr<Entity>& entity : entities)
    {
        entity->Reset();
    }

    camera = { 0 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    // Puts player in view of camera
    camera.target.x = GetEntityOfType<Player>()->x - (CELL_SIZE*5);
    camera.target.y = GetEntityOfType<Player>()->y - (CELL_SIZE*5);

    cells.clear();
    for (int x = 0; x < WIDTH/CELL_SIZE; x++)
    {
        for (int y = 0; y < HEIGHT/CELL_SIZE; y++)
        {
            cells.push_back({camera.target.x + x*CELL_SIZE, camera.target.y + y*CELL_SIZE, CELL_SIZE, CELL_SIZE});
        }
    }
}