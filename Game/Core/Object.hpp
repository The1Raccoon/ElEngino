#pragma once


#include "..\include\raylib.h"
#include "..\include\raymath.h"
#include "Globals.hpp"
#include <cstdio>  
#include <string>
#include <vector>
#include <algorithm>

namespace Core::Object
{
	class Object
	{
	private:
		inline static std::vector<Object*> AllObjects;

	public:

		Vector2 position = {0,0};

		Vector2 Velocity;

		float rotation = 0;

		float GravityScale = 0;

		bool IsKinematic = true;

		int layer = 0;

		bool RenderWorldSpace = false;

		bool Culled = false;

		virtual Vector2 GetSize() const { return { 0.0f, 0.0f }; }

		virtual void Update() {};

		virtual void Draw() {}

		virtual ~Object()
		{
			std::erase(AllObjects, this);
		}

		Object()
		{
			AllObjects.push_back(this);
		}

		static const std::vector<Object*>& GetAllObjects() {
			return AllObjects;
		}

		bool IsOnScreen()
		{
			const Vector2 size = GetSize();

			float viewLeft, viewTop, viewRight, viewBottom;

			if (RenderWorldSpace)
			{
				viewLeft = Core::Globals::Window::CamTopLeft.x;
				viewTop = Core::Globals::Window::CamTopLeft.y;
				viewRight = Core::Globals::Window::CamBottomRight.x;
				viewBottom = Core::Globals::Window::CamBottomRight.y;
			}
			else
			{
				viewLeft = 0;
				viewTop = 0;
				viewRight = (float)Core::Globals::Window::RenderWidth;
				viewBottom = (float)Core::Globals::Window::RenderHeight;
			}

			bool isHidden =
				position.x + size.x < viewLeft ||
				position.x          > viewRight ||
				position.y + size.y < viewTop ||
				position.y          > viewBottom;

			Culled = isHidden;
			return !isHidden;
		}

		void InternalUpdate()
		{
			if (!IsOnScreen()) return;

			if (!IsKinematic)
			{
				position += Velocity * Core::Globals::Engine::DeltaTime;

				if (GravityScale > 0)
				{
					Velocity.y += GravityScale * 9.81 * Core::Globals::Engine::DeltaTime;
				}
			}

			Update();
		}

		void Destroy()
		{
			delete this;
		}
	};
}