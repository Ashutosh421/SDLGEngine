#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <string>
#include "../Utils/Input.h"
#include "../Utils/Display.h"
#include "../Utils/Time.h"

namespace AREngine {
	enum EngineStatus
	{
		RUNNING,
		CLOSED
	};

	class Engine
	{
	private:
		static SDL_Event sdlEvent;
	public:
		static EngineStatus engineStatus;
		static void Init();

		static void Close();
		static void PollEvents();
	};
}

