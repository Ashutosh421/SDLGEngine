#include "Display.h"

namespace AREngine {
	Display::Display(std::string title, short width, short height) :m_title(title), m_width(width), m_height(height)
	{
		m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, SDL_WINDOW_SHOWN);
		if (m_window == NULL)
		{
			std::cout << "Coudln't create the SDL Window " << SDL_GetError() << std::endl;
		}
		m_Renderer = SDL_GetRenderer(m_window);
		if (m_Renderer == NULL)
		{
			std::cout << "SDL couldn't create the Renderer! " << "Creating the Renderer now.. ";
			m_Renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
			if (m_Renderer == NULL)
			{
				std::cout << "SDL couldn't create the Renderer! " << SDL_GetError();
				return;
			}
			else
			{
				std::cout << "SDL successfully created a Renderer " << std::endl;
			}
		}
	}

	void Display::Update()
	{
		SDL_RenderPresent(this->m_Renderer);
	}

	void Display::Clear() {
		SDL_SetRenderDrawColor(this->m_Renderer, 125, 125, 255, 255);
		SDL_RenderClear(this->m_Renderer);
	}

	Display::~Display()
	{
		SDL_DestroyRenderer(m_Renderer);
		SDL_DestroyWindow(m_window);
	}
}