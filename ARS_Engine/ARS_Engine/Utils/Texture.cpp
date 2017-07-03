#include "Texture.h"

namespace AREngine {

	Texture::Texture(std::string fileName, SDL_Renderer* mainRenderer)
	{
		active = false;
		texture = NULL;
		m_position = Vector2(0, 0);
		m_size = Vector2(0, 0);
		pivot = Pivot::TOP_LEFT;
		imageSurface = TextureResource::GetTextureSurface(fileName);

		if (imageSurface == NULL)
		{
			std::cout << "Couldn't get from the Texture Resource " << std::endl;
		}
		else {
			//std::cout << "Got it from the Texture Resource " << std::endl;
			texture = SDL_CreateTextureFromSurface(mainRenderer, imageSurface);
			if (texture == NULL)
			{
				std::cout << "Couldn't create the Texture from surface " << SDL_GetError() << std::endl;
				return;
			}
			else
			{
				active = true;
				m_size = Vector2(imageSurface->w, imageSurface->h);
				sizeRect = { 0 , 0 , imageSurface->w , imageSurface->h };
				displayRect = { 0, 0 , imageSurface->w, imageSurface->h };
			}
		}
	}

	void Texture::Update(SDL_Renderer* mainRenderer) const {
		if (!active)
		{
			return;
		}
		SDL_RenderCopy(mainRenderer, texture, &sizeRect, &displayRect);
	}

	void Texture::SetPosition(const Vector2& val) {
		this->m_position = val;
		displayRect = { (int)m_position.x, (int)m_position.y , (int)m_size.x , (int)m_size.y };
		if (pivot == Pivot::CENTER)
		{
			displayRect = { (int)m_position.x - (int)(m_size.x / 2), (int)m_position.y - (int)(m_size.y / 2) , (int)m_size.x , (int)m_size.y };
		}
	}

	const Vector2& Texture::GetPosition() const {
		return this->m_position;
	}


	void Texture::SetSize(const Vector2& val) {
		this->m_size = val;
		displayRect = { (int)m_position.x, (int)m_position.y , (int)m_size.x , (int)m_size.y };
		if (pivot == Pivot::CENTER)
		{
			displayRect = { (int)m_position.x - (int)(m_size.x / 2), (int)m_position.y - (int)(m_size.y / 2) , (int)m_size.x , (int)m_size.y };
		}
	}

	void Texture::SetPivot(const Pivot& pivot) {
		this->pivot = pivot;
		if (this->pivot == Pivot::CENTER)
		{
			displayRect = { (int)m_position.x - (int)(m_size.x / 2), (int)m_position.y - (int)(m_size.y / 2) , (int)m_size.x , (int)m_size.y };
		}
		else if (this->pivot == Pivot::TOP_LEFT) {
			displayRect = { (int)m_position.x, (int)m_position.y , (int)m_size.x , (int)m_size.y };
		}
	}

	const Vector2& Texture::GetSize() const {
		return m_size;
	}

	const bool& Texture::Is_Active() const {
		return active;
	}

	void Texture::SetActive(const bool& val) {
		this->active = val;
	}

	Texture::~Texture()
	{
		SDL_FreeSurface(imageSurface);
		SDL_DestroyTexture(texture);
	}
}