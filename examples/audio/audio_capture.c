/*******************************************************************************************
*
*   raylib [audio] example - Audio capture
*
*   Example complexity rating: [★★★★] 4/4
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2025-2025 Andreas Vennström (@avennstrom)
*
********************************************************************************************/

#include "raylib.h"
#include <math.h>

#define BUFFER_SIZE (64 * 1024)

static float buffer[2 * BUFFER_SIZE];
static size_t bufferHead = 0;

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [audio] example - audio capture");

    InitAudioDevice();              // Initialize audio device
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        size_t nread = GetAudioCaptureData(buffer + bufferHead, BUFFER_SIZE - bufferHead);
        if (nread > 0)
        {
            bufferHead = (bufferHead + nread) % BUFFER_SIZE;
        }

        BeginDrawing();
        {
            ClearBackground(RAYWHITE);

            DrawLine(
                bufferHead * ((float)screenWidth / BUFFER_SIZE), 0,
                bufferHead * ((float)screenWidth / BUFFER_SIZE), screenHeight,
                RED);

            for (int i = 0; i < (BUFFER_SIZE - 2); i += 2)
            {
                const float x0 = (i + 0) * ((float)screenWidth / BUFFER_SIZE);
                const float x1 = (i + 2) * ((float)screenWidth / BUFFER_SIZE);
                const float y0 = buffer[i + 0] * 200 + 225;
                const float y1 = buffer[i + 2] * 200 + 225;

                DrawLine(x0, y0, x1, y1, ColorLerp(GREEN, RED, fabsf(buffer[i + 0])));
            }
        }
        EndDrawing();
    }

    CloseAudioDevice();         // Close audio device (music streaming is automatically stopped)
    CloseWindow();              // Close window and OpenGL context

    return 0;
}
