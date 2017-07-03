#pragma once
#include <string>
#include <SDL_image.h>
#include "TextureResource.h"
#include "../Maths/Vector.h"


using namespace AREngine::CoolMath;

namespace AREngine {
	enum Pivot
	{
		TOP_LEFT,
		CENTER
	};

	class Texture
	{

	private:
		SDL_Rect displayRect;
		SDL_Rect sizeRect;
		Vector2 m_position;
		Vector2 m_size;
		SDL_Surface* imageSurface;
		bool active;
		Pivot pivot;

	public:
		SDL_Texture* texture;

		Texture(std::string, SDL_Renderer* mainRenderer);

		void Update(SDL_Renderer*) const;

		void SetPosition(const Vector2&);
		const Vector2& GetPosition() const;

		void SetSize(const Vector2&);
		const Vector2& GetSize() const;

		const bool& Is_Active() const;
		void SetActive(const bool&);

		void SetPivot(const Pivot& pivot);

		inline const Pivot& CheckPivot() const {
			return pivot;
		}

		~Texture();
	};
}

