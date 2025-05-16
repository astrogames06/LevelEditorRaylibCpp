#include "Player.hpp"

#include <iostream>

#include "../Game/Game.hpp"

extern Game game;

void Player::Init()
{

    rec = {(float)x,(float)y, game.CELL_SIZE, game.CELL_SIZE};
}

void Player::Update()
{
    // Player collision and movement ! AI GENERATED !
    float dt = GetFrameTime();
    const float gravity = 500.0f;
    const float jumpForce = -300.0f;
    const float moveSpeed = 200.0f;

    if (IsKeyDown(KEY_LEFT)) velocity.x = -moveSpeed;
    else if (IsKeyDown(KEY_RIGHT)) velocity.x = moveSpeed;
    else velocity.x = 0;

    velocity.y += gravity * dt;

    x += velocity.x * dt;
    rec.x = (float)x;
    for (const Rectangle& block : game.blocks) {
        if (CheckCollisionRecs(rec, block)) {
            if (velocity.x > 0) x = block.x - rec.width;
            else if (velocity.x < 0) x = block.x + block.width;
            velocity.x = 0;
            rec.x = (float)x;
        }
    }

    y += velocity.y * dt;
    rec.y = (float)y;

    isOnGround = false;
    for (const Rectangle& block : game.blocks) {
        if (CheckCollisionRecs(rec, block)) {
            if (velocity.y > 0) {
                y = block.y - rec.height;
                velocity.y = 0;
                isOnGround = true;
            }
            else if (velocity.y < 0) {
                y = block.y + block.height;
                velocity.y = 0;
            }
            rec.y = (float)y;
        }
    }

    static bool canJump = true;
    if (isOnGround && IsKeyDown(KEY_SPACE) && canJump) {
        velocity.y = jumpForce;
        isOnGround = false;
        canJump = false;
    }
    if (!IsKeyDown(KEY_SPACE)) {
        canJump = true;
    }
}

void Player::Draw()
{
    DrawRectangle(x, y, game.CELL_SIZE, game.CELL_SIZE, BLUE);
}