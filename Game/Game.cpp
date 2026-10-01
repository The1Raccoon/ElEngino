#include <iostream>
#include "include/raylib.h"
#include "include/raymath.h"
#include "Core/Object.hpp"
#include "Core/UI/Button.hpp"
#include "Core/Globals.hpp"
#include <algorithm>
#include <format>


int main(void)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT );  

    //SetConfigFlags(FLAG_WINDOW_UNDECORATED);

    const int screenWidth = 720;
    const int screenHeight = 480;

    InitWindow(screenWidth, screenHeight, "basic window");

    Core::Globals::Resources::LoadResources();


    Core::Globals::Engine::MainCamera = Camera2D{
        .offset = Vector2{ Core::Globals::Window::RenderWidth / 2.0f, Core::Globals::Window::RenderHeight / 2.0f },
        .target = Vector2{ 0, 0 },
        .rotation = 0.0f,
        .zoom = 1.0f
    };

    //SetTargetFPS(240);

    const int perRow = 125;
    const int count = 7500;
    const float btnW = 10.0f, btnH = 10.0f, gap = 5.0f;

    Core::UI::Button::Button* greg = nullptr;

    for (int i = 0; i < count; i++)
    {
        int col = i % perRow;
        int row = i / perRow;

        const std::string id = std::to_string(i);

        auto btn = new Core::UI::Button::Button(
            Vector2{ 10.0f + col * (btnW + gap), 50.0f + row * (btnH + gap) },
            btnW, btnH, std::format("this buttons id is GIBBRISH {}", i), [i]() { printf("fent %i \n", i); });

        btn->RenderWorldSpace = true;

        //test velocity stuff

        /*if (i == 1)
        {
            btn->IsKinematic = false;
            btn->Velocity.x = 100;
            btn->position.y = 1;
            std::cout << btn->IsKinematic << std::endl;
        }*/

    }

    while (!WindowShouldClose())   
    {

        Core::Globals::Window::Update();

        auto objects = Core::Object::Object::GetAllObjects();

        for (auto* o : objects)
        {
            o->InternalUpdate();
        }


        std::stable_sort(objects.begin(), objects.end(),
            [](auto* a, auto* b) { return a->layer < b->layer; });

        BeginDrawing();
        
        ClearBackground(RAYWHITE);




        BeginMode2D(Core::Globals::Engine::MainCamera);
        for (auto* o : objects)
        {
            if (o->RenderWorldSpace && !o->Culled)
            {
                o->Draw();
            }
        }
        EndMode2D();

        for (auto* o : objects)
        {
            if (!o->RenderWorldSpace && !o->Culled)
            {
                o->Draw();
            }
        }


        if (IsKeyDown(KEY_W))              Core::Globals::Engine::MainCamera.target.y -= 100 * Core::Globals::Engine::DeltaTime;
        if (IsKeyDown(KEY_S))              Core::Globals::Engine::MainCamera.target.y += 100 * Core::Globals::Engine::DeltaTime;
        if (IsKeyDown(KEY_A))              Core::Globals::Engine::MainCamera.target.x -= 100 * Core::Globals::Engine::DeltaTime;
        if (IsKeyDown(KEY_D))              Core::Globals::Engine::MainCamera.target.x += 100 * Core::Globals::Engine::DeltaTime;


        DrawLine(0, 0, GetMouseX(), GetMouseY(), RED);


        std::string formattedText = std::format("{} , {}", Core::Globals::Window::RenderHeight, Core::Globals::Window::RenderWidth);
        DrawTextEx(Core::Globals::Resources::MinecraftFont, formattedText.c_str(), Vector2{ (Core::Globals::Window::RenderWidth / 2) - (MeasureTextEx(Core::Globals::Resources::MinecraftFont,formattedText.c_str(),25.0f,1.0f).x / 2), ((float)Core::Globals::Window::RenderHeight / 2) - 15}, 25.0f, 1.0f, GREEN);


        DrawCircleV(Core::Globals::Window::ScreenMousePosition, 6, BLUE);

        DrawFPS(10, 10);

        Core::Globals::Engine::GetDT();

        EndDrawing();
    }

    CloseWindow();        

    return 0;
}
