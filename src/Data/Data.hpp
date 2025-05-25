#ifndef DATA_H
#define DATA_H

#include "nlohmann/json.hpp"
using json = nlohmann::json;

void LoadDataJSON();
void SaveDataJSON();

#endif