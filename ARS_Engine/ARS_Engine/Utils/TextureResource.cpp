#include "TextureResource.h"

namespace AREngine {
	std::unordered_map<std::string, SDL_Surface*> TextureResource::textureResource;

	void TextureResource::AddTextureToResource(std::string fileName) {
		SDL_Surface *imageSurface = IMG_Load(fileName.c_str());
		if (imageSurface == NULL)
		{
			std::cout << "Couldn't add " << fileName << "to Texture Resource " << IMG_GetError() << std::endl;
		}
		else
		{
			//std::cout << "Successfully added to the Texture Resource " << std::endl;
		}
		std::unordered_map<std::string, SDL_Surface*>::const_iterator it;
		it = textureResource.find(fileName);
		if (it == textureResource.end())
		{
			textureResource.insert(std::make_pair(fileName, imageSurface));
		}
	}

	SDL_Surface* TextureResource::GetTextureSurface(std::string fileName) {
		std::unordered_map<std::string, SDL_Surface*>::const_iterator it;
		it = textureResource.find(fileName);
		if (it == textureResource.end())
		{
			std::cout << "Couldn't find " << fileName << " at texture resource." << std::endl;
		}
		else {
			return textureResource.at(fileName);
		}
	}
	void TextureResource::Clear() {
		//std::cout << "Texture Resource clear called " << 
		std::unordered_map<std::string, SDL_Surface*>::const_iterator it;
		for (it = textureResource.begin(); it != textureResource.end(); ++it) {
			SDL_FreeSurface(it->second);
		}
	}
}


