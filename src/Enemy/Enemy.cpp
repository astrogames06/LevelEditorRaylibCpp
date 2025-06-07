#include "Enemy.hpp"

#include <iostream>

#include "../Game/Game.hpp"
#include "../Block/Block.hpp"

extern Game game;

Texture2D left_texture;
Texture2D right_texture;

void Enemy::Init()
{
    texture = LoadTexture("assets/enemy.png");
    SetTextureFilter(texture, TEXTURE_FILTER_POINT);

    left_texture = texture;

    Image flipped_img = LoadImageFromTexture(texture);
    ImageFlipHorizontal(&flipped_img);
    right_texture = LoadTextureFromImage(flipped_img);
}

void Enemy::Update()
{
    Player* player = game.GetEntityOfType<Player>();
    // Check if player lands on top of enemy
    if (!player->isOnGround &&
        player->x + game.CELL_SIZE > x &&
        player->velocity.y > 0 &&
        CheckCollisionRecs({
            (float)player->x, (float)player->y, game.CELL_SIZE, game.CELL_SIZE
        }, {(float)x, (float)y, game.CELL_SIZE, game.CELL_SIZE}))
    {
        this->Kill();
    }
    // Check if player gets hit on side of enemy
    else if (player->isOnGround && CheckCollisionRecs({
            (float)player->x, (float)player->y, game.CELL_SIZE, game.CELL_SIZE
        }, {(float)x, (float)y, game.CELL_SIZE, game.CELL_SIZE}))
    {
        player->Kill();
    }

    // Enemy collision and movement ! AI GENERATED !
    float dt = GetFrameTime();
    const float gravity = 500.0f;
    const float jumpForce = -300.0f;
    const float moveSpeed = 200.0f;

    // if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) velocity.x = -moveSpeed;
    // else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) velocity.x = moveSpeed;
    // else velocity.x = 0;

    velocity.y += gravity * dt;

    // std::cout << velocity.x << " " << velocity.y << " " << isOnGround << '\n';

    // LEFT AND RIGHT
    if (isOnGround)
        velocity.x = direction ? moveSpeed : -moveSpeed;
    else
        velocity.x = direction ? (moveSpeed/3) : -(moveSpeed/3);
    
    x += velocity.x * dt;
    for (const Block* block : game.GetEntitiesOfType<Block>()) {
        if (CheckCollisionRecs({(float)x, (float)y, game.CELL_SIZE, game.CELL_SIZE},
            {(float)block->x, (float)block->y, game.CELL_SIZE, game.CELL_SIZE}
        )) {
            if (velocity.x > 0) x = block->x - game.CELL_SIZE;
            else if (velocity.x < 0) x = block->x + game.CELL_SIZE;

            direction = !direction;
            texture = (direction) ? right_texture : left_texture;
            break;
        }
    }

    // TOP AND BOTTOM
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
        if (CheckCollisionRecs(groundCheck, 
            {(float)block->x, (float)block->y, game.CELL_SIZE, game.CELL_SIZE}
        )) {
            isOnGround = true;
            break;
        }
    }
}

void Enemy::Draw()
{
    DrawTexture(texture, x, y, WHITE);
}

void Enemy::Reset()
{
    Entity::Reset();
    isOnGround = false;
    x = origin_pos.x;
    y = origin_pos.y;
    velocity = {0, 0};
    if (direction)
    {
        Image flipped_img = LoadImageFromTexture(texture);
        ImageFlipHorizontal(&flipped_img);
        texture = LoadTextureFromImage(flipped_img);
    }
    direction = false;
}