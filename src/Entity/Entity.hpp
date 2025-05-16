#ifndef ENTITY_H
#define ENTITY_H

#include <raylib.h>

class Entity
{
public:
    int x;
    int y;
    Texture2D tex;

    virtual ~Entity() = default;
    virtual void Init() {}
    virtual void Update() {}
    virtual void Draw() {}
};

#endif