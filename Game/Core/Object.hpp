#pragma once


#include "..\include/raylib.h"
#include "..\include/raymath.h"
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
		virtual void Update() {};


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
	};
}