#include "Player.hpp"

#include <iostream>

#include "../Game/Game.hpp"

extern Game game;

void Player::Init()
{
    rec = {origin_pos.x, origin_pos.y, game.CELL_SIZE, game.CELL_SIZE};
}

bool selected = false;

void Player::Update()
{
    x = rec.x;
    y = rec.y;
    // Moving player in MOVE mode
    if (game.mode == MOVE)
    {
        std::cout << "x : " << game.world_mouse_pos.x << ", y : " << game.world_mouse_pos.y << '\n';

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), rec))
        {
            rec.x = GetMouseX();
            rec.y = GetMouseY();
            selected = true;
        }

        if (selected)
        {
            rec.x = game.world_mouse_pos.x;
            rec.y = game.world_mouse_pos.y;
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && selected)
        {
            origin_pos = game.world_mouse_pos;
            rec.x = game.world_mouse_pos.x;
            rec.y = game.world_mouse_pos.y;
            selected = false;
        }
    }

    // Player collision and movement ! AI GENERATED !
    if (game.running)
    {
        float dt = GetFrameTime();
        const float gravity = 500.0f;
        const float jumpForce = -300.0f;
        const float moveSpeed = 200.0f;

        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) velocity.x = -moveSpeed;
        else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) velocity.x = moveSpeed;
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

void Player::Draw()
{
    DrawRectangleRec(rec, BLUE);
}