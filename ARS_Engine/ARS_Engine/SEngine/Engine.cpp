#include "Engine.h"

namespace AREngine {
	SDL_Event Engine::sdlEvent;
	EngineStatus Engine::engineStatus;

	void Engine::Init() {
		//SDL Initialization
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			std::cout << "SDL couldn't initialize successfully " << SDL_GetError() << std::endl;
			return;
		}
		Uint8 flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
		Uint8 init = IMG_Init(flags);
		if ((init&flags) != flags)
		{
			std::cout << "SDL Image couldn't initialize succesfullt " << IMG_GetError() << std::endl;
		}
		Uint8 flags_Mixer = MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_FLAC;
		Uint8 initMixer = Mix_Init(flags_Mixer);
		if ((initMixer&flags_Mixer) != flags_Mixer)
		{
			std::cout << "SDL_Mixer couldn't intialize " << Mix_GetError() << std::endl;
		}

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
		{
			std::cout << "Mix Open Audio Issue " << Mix_GetError() << std::endl;
		}
		engineStatus = EngineStatus::RUNNING;
	}

	void Engine::PollEvents() {
		while (SDL_PollEvent(&sdlEvent))
		{
			Input::HandleInput(sdlEvent);
			if (sdlEvent.type == SDL_QUIT)
			{
				engineStatus = EngineStatus::CLOSED;
				break;
			}
		}
		Time::UpdateTime();
	}


	void Engine::Close() {
		Mix_CloseAudio();
		Mix_Quit();
		IMG_Quit();
		SDL_Quit();
	}
}

