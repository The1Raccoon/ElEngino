#pragma once

#include "..\..\..\include\raylib.h"
#include "..\..\..\include\raymath.h"
#include "..\..\Object.hpp"
#include "..\..\Globals.hpp"
#include "..\Frame.hpp"
#include <string>
#include <vector>

namespace Core::UI::Text::BoundText
{
	class BoundText
	{
	public:
		static void DrawBoundText(Font font, const char* text, Vector2 pos, Rectangle bounds, float fontSize, float spacing, Color color)
		{
			std::string rawText(text);
			std::string formattedText = "";
			std::string currentLine = "";

			for (char c : rawText) {
				if (c == '\n') {
					formattedText += currentLine + "\n";
					currentLine = "";
					continue;
				}

				std::string testLine = currentLine + c;
				Vector2 textScale = MeasureTextEx(font, testLine.c_str(), (float)fontSize, spacing);

				if (textScale.x > bounds.width) {
					formattedText += currentLine + "\n";
					currentLine = c;
				}
				else {
					currentLine = testLine;
				}
			}

			formattedText += currentLine;

			DrawTextEx(font, formattedText.c_str(), pos, fontSize, spacing, color);
		}
	};
}
