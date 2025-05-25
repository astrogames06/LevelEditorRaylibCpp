#ifndef BLOCK_H
#define BLOCK_H

#include <raylib.h>
#include "../Game/Game.hpp"
#include "../Entity/Entity.hpp"

extern Game game;

class Block : public Entity {
public:
    Block(float x, float y) {
        this->type = ENTITY_TYPE::BLOCK_TYPE;
        this->x = x;
        this->y = y;
    }

    void Draw() override {
        DrawRectangle(x, y, game.CELL_SIZE, game.CELL_SIZE, RED);
    }
};

#endif
