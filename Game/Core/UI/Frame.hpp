#pragma once

#include "..\..\include/raylib.h"
#include "..\..\include/raymath.h"
#include "..\Object.hpp"
#include "..\Globals.hpp"
#include <cstdio>  
#include <string>
#include <functional>

namespace Core::UI::Frame
{
	class Frame : Core::Object::Object
	{
	public:
		std::string text = "fent burger";

		Rectangle boxBounds = { 200.0f, 150.0f, 300.0f, 100.0f };

		bool visible = false;

		Frame() { layer = 100; }

		void Draw() override
		{
			if (!visible) return;

			Vector2 m = Core::Globals::Window::MousePosition;
			boxBounds.x = m.x;
			boxBounds.y = m.y;


			DrawRectangleRec(boxBounds, BLUE);

			DrawText(TextFormat(text.c_str(), boxBounds.x, boxBounds.y), boxBounds.x + 10, boxBounds.y + 10, 20, WHITE);

			visible = false;  
		}
	};
}