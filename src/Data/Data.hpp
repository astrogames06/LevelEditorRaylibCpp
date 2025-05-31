#ifndef DATA_H
#define DATA_H

#include "nlohmann/json.hpp"
using json = nlohmann::json;

#ifdef __cplusplus
extern "C" {
#endif

void LoadDataJSON(const char* json_str);
void SaveDataJSON();

#ifdef __cplusplus
}
#endif

#endif
