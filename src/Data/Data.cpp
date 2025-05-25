#include "Data.hpp"

#include <fstream>

#include "../Game/Game.hpp"

#include "../Shroom/Shroom.hpp"
#include "../Enemy/Enemy.hpp"
#include "../Block/Block.hpp"

extern Game game;

json j = json::array();

void SaveDataJSON()
{
    for (std::unique_ptr<Entity>& entity : game.entities)
    {
        j.push_back({
            {"type", entity->type},
            {"x", entity->x},
            {"y", entity->y}
        });
    }

    std::ofstream file("data.json", std::ios::trunc);
    if (file.is_open()) {
        file << j.dump(4);
    }
}

void LoadDataJSON()
{
    std::ifstream file("data.json");
    if (!file.is_open()) return;

    json j_loaded;
    file >> j_loaded;

    // Clears entites to re-add them but only removes ones that arent player
    Player* player = game.GetEntityOfType<Player>();
    game.entities.erase(
        std::remove_if(game.entities.begin(), game.entities.end(),
            [player](const std::unique_ptr<Entity>& e) {
                return e.get() != player;
            }),
        game.entities.end()
    );

    for (json::reference item : j_loaded)
    {
        // Gets entity info
        int type_enum = item.at("type").get<int>();
        int x = item.at("x").get<int>();
        int y = item.at("y").get<int>();

        switch(type_enum)
        {
            case ENTITY_TYPE::PLAYER_TYPE:
                game.GetEntityOfType<Player>()->origin_pos = {(float)x, (float)y};
                game.GetEntityOfType<Player>()->x = x;
                game.GetEntityOfType<Player>()->y = y;
                game.GetEntityOfType<Player>()->Init();
                break;
            case ENTITY_TYPE::BLOCK_TYPE:
                game.entities.push_back(std::make_unique<Block>(x, y));
                break;
            case ENTITY_TYPE::ENEMY_TYPE:
                game.entities.push_back(std::make_unique<Enemy>(x, y));
                break;
            case ENTITY_TYPE::SHROOM_TYPE:
                game.entities.push_back(std::make_unique<Shroom>(x, y));
                break;
            default:
                break;
        }
    }
}