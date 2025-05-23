#ifndef PLAYER_H
#define PLAYER_H

#include "../Entity/Entity.hpp"

class Player : public Entity
{
public:
    Vector2 velocity = {0, 0};
    bool isOnGround;

    Vector2 origin_pos;

    void Init() override;
    void Update() override;
    void Draw() override;
    void Reset() override;
};

#endif