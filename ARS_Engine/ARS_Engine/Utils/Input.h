#pragma once
#include <SDL.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>


namespace AREngine {
	enum MOUSE_BUTTON
	{
		LEFT,
		MIDDLE,
		RIGHT
	};


	class Input
	{
	public:

	private:
		static std::unordered_map<SDL_Scancode, bool> keys;
		static std::unordered_map<SDL_Scancode, bool>::const_iterator keysIterator;

		static std::unordered_map<SDL_Scancode, bool> keysState_SaverUP;
		static std::unordered_map<SDL_Scancode, bool> keysState_SaverDown;

		static std::unordered_map<MOUSE_BUTTON, bool> mouseButtons;
		static std::unordered_map<MOUSE_BUTTON, bool>::const_iterator mouseButtoniterator;

		static std::unordered_map<MOUSE_BUTTON, bool> mouseButton_SaverUp;
		static std::unordered_map<MOUSE_BUTTON, bool> mouseButton_SaverDown;

	public:
		static void HandleInput(SDL_Event);

		static bool IsKeyDown(SDL_Scancode keyCode);

		static bool IsKeyDown_Repeat(SDL_Scancode keyCode);

		static bool IsKeyUp(SDL_Scancode keyCode);

		static bool IsMouseButtonDown(MOUSE_BUTTON);

		static bool IsMouseButton_Repeat(MOUSE_BUTTON);

		static bool IsMouseButtonUp(MOUSE_BUTTON);

	};
}

