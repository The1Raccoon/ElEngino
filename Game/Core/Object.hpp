#pragma once


#include "..\include\raylib.h"
#include "..\include\raymath.h"
#include "Globals.hpp"
#include <cstdio>  
#include <string>
#include <vector>

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

		virtual void Update() {};

		virtual void Draw() {}

		virtual ~Object()
		{
			AllObjects.erase(std::remove(AllObjects.begin(), AllObjects.end(), this), AllObjects.end());
		}

		Object()
		{
			AllObjects.push_back(this);
		}

		static const std::vector<Object*>& GetAllObjects() {
			return AllObjects;
		}

		void InternalUpdate()
		{
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