#include "raylib.h"
#include <vector>
#include <algorithm>

void draw(int w, int h, std::vector<std::vector<int>> circles)
{
    const float skala = 50.0f;

    // Novi prozor
    int screenW = (int)(w * skala) + 100;
    int screenH = (int)(h * skala) + 100;

    // Inicijalizacija velikog prozora
    if (!IsWindowReady()) {
        InitWindow(screenW, screenH, "ga MATF");
        SetTargetFPS(60);
    }

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);


        //kvadrat
        DrawRectangleLines(50, 50, (int)(w * skala), (int)(h * skala), BLACK);

        //krugovi
        for(auto &c : circles)
        {
            float cx = (float)c[0];
            float cy = (float)c[1];
            float r  = (float)c[2];

            float scaledCX = 50.0f + (cx * skala);
            float scaledCY = (50.0f + ((float)h * skala)) - (cy * skala);

            float scaledR = r * skala;

            Vector2 center = { scaledCX, scaledCY };


            DrawCircleV(center, scaledR, Fade(MAROON, 0.4f));
            DrawCircleLinesV(center, scaledR, BLACK);
        }

        // Tekst u gornjem uglu
        DrawText("Izlaz ESC", 10, 10, 15, DARKGRAY);
        //DrawText(TextFormat("Zum: x%.0f", skala), screenW - 100, 10, 20, DARKGRAY);

        EndDrawing();

        // ESC prekida vizuelizaciju
        if (IsKeyPressed(KEY_ESCAPE)) break;
    }

    // CloseWindow(); // Ne zatvaramo odmah ako ti treba prozor
}
