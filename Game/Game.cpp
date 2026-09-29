#include <iostream>
#include "include/raylib.h"
#include "include/raymath.h"
#include "Core/Object.hpp"
#include "Core/UI/Button.hpp"
#include <format>


int main(void)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT );  
    //SetConfigFlags(FLAG_WINDOW_UNDECORATED);

    const int screenWidth = 720;
    const int screenHeight = 480;



    SetConfigFlags(FLAG_MSAA_4X_HINT);

    InitWindow(screenWidth, screenHeight, "basic window");

    const int perRow = 125;
    const int count = 7500;
    const float btnW = 10.0f, btnH = 10.0f, gap = 5.0f;

    for (int i = 0; i < count; i++)
    {
        int col = i % perRow;
        int row = i / perRow;

        auto btn = new Core::UI::Button::Button(
            Vector2{ 10.0f + col * (btnW + gap), 50.0f + row * (btnH + gap) },
            btnW, btnH, "ti", Core::UI::Button::rectangle, [i]() { printf("fent %i \n" , i); });
    }


    Font customFont = LoadFont("resources/fonts/minecraftfont.ttf");

    while (!WindowShouldClose())   
    {
        BeginDrawing();
        
        ClearBackground(RAYWHITE);

        DrawLine(0, 0, GetMouseX(), GetMouseY(), RED);


        std::string formattedText = std::format("{} , {}", GetRenderHeight(), GetRenderWidth());
        DrawTextEx(customFont, formattedText.c_str(), Vector2{ ((float)GetRenderWidth() / 2) - (MeasureTextEx(customFont,formattedText.c_str(),25.0f,1.0f).x / 2), (float)GetRenderHeight() / 2}, 25.0f, 1.0f, GREEN);


        DrawCircleV(GetMousePosition(), 6, BLUE);




        for (const auto& obj : Core::Object::Object::GetAllObjects())
        {
            obj->Update();
        }


        DrawFPS(10, 10);

        EndDrawing();
        
    }

    CloseWindow();        

    return 0;
}
