#pragma once

#include "..\..\include/raylib.h"
#include "..\..\include/raymath.h"
#include "..\Object.hpp"
#include <cstdio>  
#include <string>
#include <functional>

namespace Core::UI::Button
{
	enum Orientation
	{
		centered,
		corner
	};

	class Button : Core::Object::Object
	{
		float height, width;

		bool IsMouseHovering = false;

		bool hidden = false;

		Vector2 position;

		std::string text;

	private:
		std::function<void()> onClick;

		bool IsHovering()
		{
			Rectangle btnBounds = { position.x, position.y, width, height };

			return CheckCollisionPointRec(GetMousePosition(), btnBounds);
		}

	public:
		Button(Vector2 pos = Vector2(100,30), float Width = 60.0f, float Height = 25.0f, std::string Text = "fent", std::function<void()> callback = nullptr) : onClick(callback)
		{
			width = Width;
			height = Height;
			text = Text;
			position = pos;
		};

		void click() {
			if (onClick) {
				onClick();
			}
		}

		void Update() override
		{
			hidden = position.x > GetRenderWidth() || position.y > GetRenderHeight();

			if (hidden) return;

			if (IsHovering())
			{
				DrawRectangle(position.x, position.y, width, height, GREEN);
				if (IsMouseButtonPressed(1))
				{
					click();
				}
			}
			else
			{
				DrawRectangle(position.x, position.y, width, height, RED);
			}
		}
	};
}
