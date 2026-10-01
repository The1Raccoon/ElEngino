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

		Vector2 position;

		Vector2 Velocity;

		float GravityScale = 0;

		bool IsKinematic = true;

		int layer = 0;

		bool RenderWorldSpace = false;

		bool Culled = false;

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
			bool isHidden = false;

			if (this->RenderWorldSpace)
			{
				isHidden = position.x < Core::Globals::Window::CamTopLeft.x ||
					position.x > Core::Globals::Window::CamBottomRight.x ||
					position.y < Core::Globals::Window::CamTopLeft.y ||
					position.y > Core::Globals::Window::CamBottomRight.y;
			}
			else
			{
				isHidden = position.x < 0 ||
					position.x > Core::Globals::Window::RenderWidth ||
					position.y < 0 ||
					position.y > Core::Globals::Window::RenderHeight;
			}

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