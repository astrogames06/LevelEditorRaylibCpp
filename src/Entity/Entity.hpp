#ifndef ENTITY_H
#define ENTITY_H

#include <raylib.h>

enum ENTITY_TYPE
{
    PLAYER_TYPE,
    BLOCK_TYPE,
    ENEMY_TYPE,
    SHROOM_TYPE
};

class Entity
{
public:
    ENTITY_TYPE type;
    int x;
    int y;
    Texture2D texture;
    bool remove = false;
    bool alive = true;

    virtual ~Entity() = default;
    virtual void Init() {}
    virtual void Update() {}
    virtual void Draw() {}
    virtual void Reset() { alive = true; }
    // To kill entity in game
    void Kill() { alive = false; }

    // To delete entity from game.entities
    void Delete() { remove = true; }
};

#endif