#include "Data.hpp"

#include <fstream>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

#include "../Game/Game.hpp"

extern Game game;

void SaveDataJSON()
{
    json j = {
        {"level", 1},
        {"name", "Test Level"},
        {"complete", false}
    };

    std::ofstream file("data.json");
    if (file.is_open()) {
        file << j.dump(4);
        file.close();
    }
}