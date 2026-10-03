#pragma once


#include "..\include/raylib.h"
#include "..\include/raymath.h"
#include <cstdio>  
#include <string>
#include <vector>



namespace Core::Globals
{

	class Engine
	{
	public:

		inline static float DeltaTime;

		inline static Camera2D MainCamera;

		inline static void GetDT()
		{
			DeltaTime = GetFrameTime();
		}
	};

	class Window
	{
	public:
		inline static Vector2 ScreenMousePosition;

		inline static Vector2 WorldMousePosition;

		inline static float RenderWidth;

		inline static float RenderHeight;

		inline static Vector2 CamTopLeft;

		inline static Vector2 CamBottomRight;

		static void Update()
		{
			ScreenMousePosition = GetMousePosition();

			WorldMousePosition = GetScreenToWorld2D(GetMousePosition(), Core::Globals::Engine::MainCamera);

			RenderWidth = GetRenderWidth();
			RenderHeight = GetRenderHeight();

			CamTopLeft = GetScreenToWorld2D(Vector2{ 0.0f, 0.0f }, Core::Globals::Engine::MainCamera);
			CamBottomRight = GetScreenToWorld2D(Vector2{ RenderWidth, RenderHeight }, Core::Globals::Engine::MainCamera);
		}
	};

	class Resources
	{
	public:
		inline static Font MinecraftFont;

		static void LoadResources()
		{
			MinecraftFont = LoadFont("resources/fonts/minecraftfont.ttf");
		}
	};
}