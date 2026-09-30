#pragma once


#include "..\include/raylib.h"
#include "..\include/raymath.h"
#include <cstdio>  
#include <string>
#include <vector>


namespace Core::Globals
{
	class Window
	{
	public:
		inline static Vector2 MousePosition;

		inline static float RenderWidth;

		inline static float RenderHeight;

		static void Update()
		{
			MousePosition = GetMousePosition();
			RenderWidth = GetRenderWidth();
			RenderHeight = GetRenderHeight();
		}
	};
	class Resources
	{
	public:
		inline static Font MinecraftFont;

		static void LoadResources()
		{
			MinecraftFont = LoadFont("resources/fonts/minecraftfont.ttf");

			printf("Font object address: %p\n", (void*)&MinecraftFont);
		}
	};
}