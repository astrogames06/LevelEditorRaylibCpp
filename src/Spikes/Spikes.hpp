#ifndef SPIKES_H
#define SPIKES_H

#include "../Entity/Entity.hpp"

class Spikes : public Entity
{
public:
    Spikes(float x, float y) {
        type = ENTITY_TYPE::SPIKE_TYPE;
        this->x = x;
        this->y = y;
        origin_pos = {x, y};
        Init();
    }

    void Init() override;
    void Update() override;
    void Draw() override;
};

#endif