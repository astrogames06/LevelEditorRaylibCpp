#ifndef SHROOM_H
#define SHROOM_H

#include "../Entity/Entity.hpp"

class Shroom : public Entity
{
public:
    float bounciness = 300.f;
    Shroom(float x, float y) {
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