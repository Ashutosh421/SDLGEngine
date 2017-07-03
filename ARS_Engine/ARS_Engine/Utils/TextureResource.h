#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <unordered_map>

namespace AREngine {
	class TextureResource
	{
	private:
		static std::unordered_map<std::string, SDL_Surface*> textureResource;

	public:
		static void AddTextureToResource(std::string);
		static SDL_Surface* GetTextureSurface(std::string fileName);
		static void Clear();
	};
}

