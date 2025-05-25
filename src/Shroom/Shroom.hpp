#ifndef SHROOM_H
#define SHROOM_H

#include "../Entity/Entity.hpp"

class Shroom : public Entity
{
public:
    float bounciness = 500.f;
    Shroom(float x, float y) {
        this->type = ENTITY_TYPE::SHROOM_TYPE;
        this->x = x;
        this->y = y;
        Init();
    }
    void Init() override;
    void Update() override;
    void Draw() override;
    void Reset() override;
};

#endif