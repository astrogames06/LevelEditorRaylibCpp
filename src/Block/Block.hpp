#ifndef BLOCK_H
#define BLOCK_H

#include <raylib.h>
#include "../Game/Game.hpp"
#include "../Entity/Entity.hpp"

extern Game game;

class Block : public Entity {
public:
    Rectangle rec;

    Block(float x, float y) {
        rec = {x, y, game.CELL_SIZE, game.CELL_SIZE};
        this->x = x;
        this->y = y;
    }

    void Update() override {
        rec.x = x;
        rec.y = y;
    }

    void Draw() override {
        DrawRectangleRec(rec, RED);
    }
};

#endif
