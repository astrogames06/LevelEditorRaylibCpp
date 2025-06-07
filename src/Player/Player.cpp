#include "Player.hpp"

#include <iostream>
#include <cmath>

#include "../Game/Game.hpp"
#include "../Block/Block.hpp"

extern Game game;

void Player::Init()
{
    type = ENTITY_TYPE::PLAYER_TYPE;
    x = origin_pos.x;
    y = origin_pos.y;
}

void Player::Update()
{
    // Moving player in MOVE mode
    if (game.mode == MOVE)
    {
        //std::cout << "x : " << game.world_mouse_pos.x << ", y : " << game.world_mouse_pos.y << '\n';
    }

    // Player collision and movement ! AI GENERATED !

    float dt = GetFrameTime();
    const float gravity = 500.0f;
    const float jumpForce = -300.0f;
    const float moveSpeed = 200.0f;

    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) velocity.x = -moveSpeed;
    else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) velocity.x = moveSpeed;
    else velocity.x = 0;

    velocity.y += gravity * dt;

    x += velocity.x * dt;
    for (const Block* block : game.GetEntitiesOfType<Block>()) {
        if (CheckCollisionRecs({(float)x, (float)y, game.CELL_SIZE, game.CELL_SIZE},
        {(float)block->x, (float)block->y, game.CELL_SIZE, game.CELL_SIZE}
    )) {
            if (velocity.x > 0) x = block->x - game.CELL_SIZE;
            else if (velocity.x < 0) x = block->x + game.CELL_SIZE;
            velocity.x = 0;
        }
    }

    y += velocity.y * dt;
    for (const Block* block : game.GetEntitiesOfType<Block>()) {
        if (CheckCollisionRecs({(float)x, (float)y, game.CELL_SIZE, game.CELL_SIZE}, 
            {(float)block->x, (float)block->y, game.CELL_SIZE, game.CELL_SIZE}
        )) {
            if (velocity.y > 0) {
                y = block->y - game.CELL_SIZE;
                velocity.y = 0;
            }
            else if (velocity.y < 0) {
                y = block->y + game.CELL_SIZE;
                velocity.y = 0;
            }
        }
    }
    isOnGround = false;
    Rectangle groundCheck = { (float)x, (float)y + game.CELL_SIZE + 1, game.CELL_SIZE, 2 };
    for (const Block* block : game.GetEntitiesOfType<Block>()) {
        if (CheckCollisionRecs(groundCheck, {(float)block->x, (float)block->y, game.CELL_SIZE, game.CELL_SIZE})) {
            isOnGround = true;
            break;
        }
    }

    static bool canJump = true;
    if (isOnGround && (IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) && canJump) {
        velocity.y = jumpForce;
        isOnGround = false;
        canJump = false;
    }
    if (!(IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_W))) {
        canJump = true;
    }
}

void Player::Draw()
{
    DrawRectangle(x, y, game.CELL_SIZE, game.CELL_SIZE, BLUE);

    // DrawText(std::to_string(isOnGround).c_str(), x, y, 20, BLACK);
}

void Player::Reset()
{
    Entity::Reset();
    isOnGround = false;
    x = origin_pos.x;
    y = origin_pos.y;
    velocity = {0, 0};
}

void Player::Kill()
{
    for (std::unique_ptr<Entity>& entity : game.entities) entity->Reset();
}