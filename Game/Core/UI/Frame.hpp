#pragma once

#include "..\..\include\raylib.h"
#include "..\..\include\raymath.h"
#include "..\Object.hpp"
#include "..\Globals.hpp"
#include "Text\BoundText.hpp"
#include <cstdio>  
#include <string>
#include <functional>


using namespace Core::UI::Text::BoundText;

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
			boxBounds.x = m.x + 15;
			boxBounds.y = m.y;


			DrawRectangleRec(boxBounds, BLUE);

			BoundText::DrawBoundText(Core::Globals::Resources::MinecraftFont, text.c_str(), Vector2(boxBounds.x, boxBounds.y), boxBounds, 25, 1, RED);

			visible = false;  
		}
	};
}