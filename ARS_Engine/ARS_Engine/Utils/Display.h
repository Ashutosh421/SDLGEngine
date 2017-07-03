#pragma once
#include <SDL.h>
#include <iostream>
#include <string>

namespace AREngine {
	class Display
	{
	private:
		short m_width;
		short m_height;
		std::string m_title;

	public:
		SDL_Window* m_window;
		SDL_Renderer* m_Renderer;

	public:

		Display(std::string title, short width, short height);
		void Update();
		void Clear();
		~Display();

		//Setters
		inline void SetTitle(std::string title) {
			this->m_title = title;
		}

		//Gettters
		inline short GetWidth() {
			return this->m_width;
		}

		inline short GetHeight() {
			return this->m_height;
		}

		inline std::string GetTitle() {
			return this->m_title;
		}
	};
}

