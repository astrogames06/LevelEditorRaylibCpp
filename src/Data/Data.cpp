#include "Data.hpp"

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

#include "../Game/Game.hpp"
#include "../Shroom/Shroom.hpp"
#include "../Enemy/Enemy.hpp"
#include "../Block/Block.hpp"
#include "../Spikes/Spikes.hpp"

#ifdef PLATFORM_WEB
#include <emscripten/emscripten.h>
#endif

extern Game game;

json j = json::array();

#ifdef __cplusplus
extern "C" {
#endif

void SaveDataJSON()
{
    j.clear();
    for (const std::unique_ptr<Entity>& entity : game.entities)
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

    std::string jsonStr = j.dump(4);

#ifdef PLATFORM_WEB
    std::string escapedJsonStr;
    for (char c : jsonStr)
    {
        switch (c)
        {
            case '"':  escapedJsonStr += "\\\""; break;
            case '\\': escapedJsonStr += "\\\\"; break;
            case '\n': escapedJsonStr += "\\n";  break;
            case '\r': escapedJsonStr += "\\r";  break;
            case '\t': escapedJsonStr += "\\t";  break;
            default:
                if (static_cast<unsigned char>(c) < 0x20)
                {
                    char buffer[7];
                    snprintf(buffer, sizeof(buffer), "\\u%04x", c);
                    escapedJsonStr += buffer;
                }
                else
                {
                    escapedJsonStr += c;
                }
        }
    }

    std::string jsCode =
        "var blob = new Blob([\"" + escapedJsonStr + "\"], {type: 'application/json'});"
        "var url = URL.createObjectURL(blob);"
        "var a = document.createElement('a');"
        "a.href = url;"
        "a.download = 'data.json';"
        "a.click();"
        "URL.revokeObjectURL(url);";

    emscripten_run_script(jsCode.c_str());
#endif
}


void LoadDataJSON(const char* json_str)
{
    std::cout << "C++ received JSON string:\n" << json_str << std::endl;
    // std::ifstream file("data.json");
    // if (!file.is_open()) return;

    if (!json_str) {
        std::cerr << "json_str is null!" << std::endl;
        #ifdef PLATFORM_WEB
                emscripten_run_script("alert('JSON FILES IS INVALID OR CORRUPTED!')");
        #endif
        return;
    }

    json j_loaded = json::parse(json_str);

    // Keep player, remove others
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
        int type_enum = item.at("type").get<int>();
        int x = item.at("x").get<int>();
        int y = item.at("y").get<int>();

        switch(type_enum)
        {
            case ENTITY_TYPE::PLAYER_TYPE:
                player->origin_pos = {(float)x, (float)y};
                player->x = x;
                player->y = y;
                player->Init();
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
            case ENTITY_TYPE::SPIKE_TYPE:
                game.entities.push_back(std::make_unique<Spikes>(x, y));
                break;
            default:
                break;
        }
    }

    // Resets and cleans entities
    game.Reset();
}

#ifdef __cplusplus
} // extern "C"
#endif
