#include "Enemy.hpp"

#include <iostream>

#include "../Game/Game.hpp"
#include "../Block/Block.hpp"

extern Game game;

void Enemy::Init()
{
    texture = LoadTexture("assets/enemy.png");
}

void Enemy::Update()
{
    // Player collision and movement ! AI GENERATED !
    if (game.running)
    {
        float dt = GetFrameTime();
        const float gravity = 500.0f;
        const float jumpForce = -300.0f;
        const float moveSpeed = 200.0f;

        // if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) velocity.x = -moveSpeed;
        // else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) velocity.x = moveSpeed;
        // else velocity.x = 0;

        velocity.y += gravity * dt;

        // LEFT AND RIGHT
        if (isOnGround)
            velocity.x = direction ? moveSpeed : -moveSpeed; 
        x += velocity.x * dt;
        for (const Block* block : game.GetEntitiesOfType<Block>()) {
            if (CheckCollisionRecs({(float)x, (float)y, game.CELL_SIZE, game.CELL_SIZE}, block->rec)) {
                if (velocity.x > 0) x = block->rec.x - game.CELL_SIZE;
                else if (velocity.x < 0) x = block->rec.x + block->rec.width;
                velocity.x = 0;

                direction = !direction;
                break;
            }
        }

        // TOP AND BOTTOM
        y += velocity.y * dt;
        isOnGround = false;
        for (const Block* block : game.GetEntitiesOfType<Block>()) {
            if (CheckCollisionRecs({(float)x, (float)y, game.CELL_SIZE, game.CELL_SIZE}, block->rec)) {
                if (velocity.y > 0) {
                    y = block->rec.y - game.CELL_SIZE;
                    velocity.y = 0;
                    isOnGround = true;
                }
                else if (velocity.y < 0) {
                    y = block->rec.y + block->rec.height;
                    velocity.y = 0;
                }
            }
        }

        static bool canJump = true;
        if (isOnGround && (IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_W)) && canJump) {
            velocity.y = jumpForce;
            isOnGround = false;
            canJump = false;
        }
        if (!(IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_W))) {
            canJump = true;
        }
    }
}

void Enemy::Draw()
{
    DrawTexture(texture, x, y, WHITE);
}