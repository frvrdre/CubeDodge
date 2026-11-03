
#include <cmath>
#include "raylib.h"

int main()
{
    bool gameOver{false};

    // Window
    const int screenWidth{800};
    const int screenHeight{600};

    // Player
    const float playerWidth{40.0f};
    const float playerHeight{40.0f};
    const float playerSpeed{200.0f};

    float playerX{380.0f};
    float playerY{500.0f};

    const float maxX{screenWidth - playerWidth};
    const float maxY{screenHeight - playerHeight};

    Rectangle player{
        playerX,
        playerY,
        playerWidth,
        playerHeight
    };

    // Enemy
    const float enemySize{40.0f};
    const float enemySpeed{150.0f};

    float enemyX{380.0f};
    float enemyY{0.0f};

    Rectangle enemy{
        enemyX,
        enemyY,
        enemySize,
        enemySize
    };

    // Setup
    InitWindow(screenWidth, screenHeight, "Dodge Arena");
    SetTargetFPS(999);

    while (!WindowShouldClose())
    {
        const float deltaTime{GetFrameTime()};

        // Read movement input
        float directionX{0.0f};
        float directionY{0.0f};

        if (!gameOver)
        {
            if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
            {
                directionX -= 1.0f;
            }

            if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
            {
                directionX += 1.0f;
            }

            if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
            {
                directionY -= 1.0f;
            }

            if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
            {
                directionY += 1.0f;
            }

            // Keep movement speed consistent
            const float length{
                std::sqrt(
                    directionX * directionX +
                    directionY * directionY)
            };

            if (length > 0.0f)
            {
                directionX /= length;
                directionY /= length;
            }

            // Move player
            playerX += directionX * playerSpeed * deltaTime;
            playerY += directionY * playerSpeed * deltaTime;

            // Keep player inside the window
            if (playerX > maxX)
            {
                playerX = maxX;
            }
            else if (playerX < 0.0f)
            {
                playerX = 0.0f;
            }

            if (playerY > maxY)
            {
                playerY = maxY;
            }
            else if (playerY < 0.0f)
            {
                playerY = 0.0f;
            }

            // Move enemy
            enemyY += enemySpeed * deltaTime;

            if (enemyY > screenHeight)
            {
                enemyY = -enemySize;
            }

            // Update rectangle positions
            player.x = playerX;
            player.y = playerY;

            enemy.x = enemyX;
            enemy.y = enemyY;
        }

        // Check collision
        const bool collision{
            CheckCollisionRecs(player, enemy)
        };

        if (collision)
        {
            gameOver = true;
        }

        // Draw
        BeginDrawing();
        ClearBackground(BLACK);

        // Draw gameplay
        DrawRectangleRec(player, BLUE);
        DrawRectangleRec(enemy, RED);

        // Draw Game Over overlay
        if (gameOver)
        {
            DrawRectangle(
                0,
                0,
                screenWidth,
                screenHeight,
                Fade(BLACK, 0.75f)
            );

            DrawText("GAME OVER", 280, 250, 40, RED);
        }

        // Always display FPS
        DrawText(
            TextFormat("FPS: %i", GetFPS()),
            10,
            10,
            20,
            GREEN
        );

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
