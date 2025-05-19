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
        else
            velocity.x = direction ? (moveSpeed/5) : -(moveSpeed/5);
        
        x += velocity.x * dt;
        for (const Block* block : game.GetEntitiesOfType<Block>()) {
            if (CheckCollisionRecs({(float)x, (float)y, game.CELL_SIZE, game.CELL_SIZE}, block->rec)) {
                if (velocity.x > 0) x = block->rec.x - game.CELL_SIZE;
                else if (velocity.x < 0) x = block->rec.x + block->rec.width;
                velocity.x = 0;

                Image flipped_img = LoadImageFromTexture(texture);
                ImageFlipHorizontal(&flipped_img);
                texture = LoadTextureFromImage(flipped_img);
                direction = !direction;
                break;
            }
        }

        // TOP AND BOTTOM
        y += velocity.y * dt;
        for (const Block* block : game.GetEntitiesOfType<Block>()) {
            if (CheckCollisionRecs({(float)x, (float)y, game.CELL_SIZE, game.CELL_SIZE}, block->rec)) {
                if (velocity.y > 0) {
                    y = block->rec.y - game.CELL_SIZE;
                    velocity.y = 0;
                }
                else if (velocity.y < 0) {
                    y = block->rec.y + block->rec.height;
                    velocity.y = 0;
                }
            }
        }

        isOnGround = false;
        Rectangle groundCheck = { (float)x, (float)y + game.CELL_SIZE + 1, game.CELL_SIZE, 2 };
        for (const Block* block : game.GetEntitiesOfType<Block>()) {
            if (CheckCollisionRecs(groundCheck, block->rec)) {
                isOnGround = true;
                break;
            }
        }
    }
}

void Enemy::Draw()
{
    DrawTexture(texture, x, y, WHITE);
}

void Enemy::Reset()
{
    isOnGround = false;
    x = origin_pos.x;
    y = origin_pos.y;
    velocity = {0, 0};
}