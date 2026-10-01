#pragma once

#include "..\..\include/raylib.h"
#include "..\..\include/raymath.h"
#include "..\Object.hpp"
#include "..\Globals.hpp"
#include "Frame.hpp"
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

	class Button : public Core::Object::Object
	{

	private:
		std::function<void()> onClick;

		bool IsHovering()
		{
			Rectangle btnBounds = { position.x, position.y, width, height };

			if (this->RenderWorldSpace) return CheckCollisionPointRec(Core::Globals::Window::WorldMousePosition, btnBounds);
			else
			return CheckCollisionPointRec(Core::Globals::Window::ScreenMousePosition, btnBounds);

		}

		Vector2 GetSize() const override { return { width, height }; }

	public:
		float height, width;

		bool IsMouseHovering = false;

		Core::UI::Frame::Frame* HoverFrame;

		Button(Vector2 pos = Vector2(100,30), float Width = 60.0f, float Height = 25.0f, std::string text = "null", std::function<void()> callback = nullptr) : onClick(callback)
		{
			HoverFrame = new Core::UI::Frame::Frame();

			width = Width;
			height = Height;
			position = pos;

			HoverFrame->text = text;
		};

		~Button()
		{
			delete HoverFrame;
			HoverFrame = nullptr;
		}

		void click() {
			if (onClick) {
				onClick();
			}
		}

		void Update() override
		{			
			IsMouseHovering = IsHovering();

			HoverFrame->visible = IsMouseHovering;

			if (IsMouseHovering && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				click();
		}

		void Draw() override
		{
			DrawRectangle(position.x, position.y, width, height, IsMouseHovering ? GREEN : RED);
		}
	};
}
