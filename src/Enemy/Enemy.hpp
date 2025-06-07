#ifndef ENEMY_H
#define ENEMY_H

#include "../Entity/Entity.hpp"

#include "../Data/Data.hpp"

#include "nlohmann/json.hpp"

class Enemy : public Entity
{
public:
    Vector2 velocity = {0, 0};
    bool isOnGround;
    bool direction;

    Enemy(float x, float y) {
        type = ENTITY_TYPE::ENEMY_TYPE;
        this->x = x;
        this->y = y;
        origin_pos = {x, y};
        Init();
    }
    void Init() override;
    void Update() override;
    void Draw() override;
    void Reset() override;
};

#endif