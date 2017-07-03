#include "SpriteAnimation.h"

namespace AREngine {
	SpriteAnimation::SpriteAnimation(std::string fileName, SDL_Renderer* mainRenderer)
	{
		pivot = Pivot::TOP_LEFT;
		active = false;
		texture = NULL;
		imageSurface = NULL;
		m_position = Vector2(0, 0);
		m_angle = 0.0f;
		m_animationMode = Animation_Mode::ONCE;
		m_spriteAnimationFrequency = 0.1f;
		debug = false;

		m_velocity = Vector2(0, 0);
		m_gravity = 0;
		m_mass = 0;
		m_activateGravity = false;
		m_accelertion = Vector2(0, 0);

		imageSurface = TextureResource::GetTextureSurface(fileName);
		if (imageSurface == NULL)
		{
			std::cout << "Couldn't get Sprite Animation Sheet " << fileName << " from the Texture Resource " << std::endl;
		}
		else
		{
			//	std::cout << "Successfully loaded the Sprite Animation Sheet " << std::endl;
			texture = SDL_CreateTextureFromSurface(mainRenderer, imageSurface);
			if (texture == NULL)
			{
				std::cout << "Couldn't create Sprite Animation Sheet Texture " << SDL_GetError() << std::endl;
				return;
			}
			else
			{
				active = true;
				//	std::cout << "SDL Texture Successfully created" << std::endl;
				currentFrameDisplay_Rect = { 0 , 0 , imageSurface->w , imageSurface->h };
				m_size = Vector2(imageSurface->w, imageSurface->h);
				if (pivot == Pivot::CENTER)
				{
					destination_Rect = { (int)m_position.x - (int)(m_size.x / 2), (int)m_position.y - (int)(m_size.y / 2) , (int)m_size.x , (int)m_size.y };
				}
			}
		}
	}

	void SpriteAnimation::AddFrame(const int& x, const int& y, const int& w, const int& h)
	{
		this->frames.push_back({ x , y , w , h });
		std::vector<SDL_Rect>::iterator it;
	}

	void SpriteAnimation::SetGravity(const float& gravity) {
		this->m_gravity = gravity;
	}

	void SpriteAnimation::SetMass(const float& mass) {
		this->m_mass = mass;
	}

	const float& SpriteAnimation::Mass() {
		return this->m_mass;
	}

	void SpriteAnimation::ActivateGravity(const bool& activate) {
		this->m_activateGravity = activate;
	}

	void SpriteAnimation::SetVelocity(const Vector2& velocity) {
		this->m_velocity = velocity;
	}

	void SpriteAnimation::SetAcceleration(const Vector2& acceleration) {
		m_accelertion = acceleration;
	}

	void SpriteAnimation::Update(SDL_Renderer* mainRenderer) {
		if (!active)
		{
			return;
		}
		SDL_RenderCopyEx(mainRenderer, texture, &currentFrameDisplay_Rect, &destination_Rect, m_angle, NULL, SDL_FLIP_NONE);

		if (m_position.y - m_size.y / 2 <= 0)
		{
			m_position.y = m_size.y / 2;
			m_velocity = Vector2(0, 200);
			m_angle = 0;
		}
		else
		{
			m_velocity += m_accelertion * Time::deltaTime;
		}
		m_position += m_velocity * Time::deltaTime;

		if (m_activateGravity)
		{
			m_velocity.y += (m_gravity * m_mass) * Time::deltaTime;
		}
		SetPosition(m_position);

		if (playAnim)
		{
			m_currentTime = Time::time;
			if (m_currentTime >= m_changeTime)
			{
				if (debug)
				{
					std::cout << "Current Time " << m_currentTime << std::endl;
					std::cout << "Change Time " << m_changeTime << std::endl;
				}
				currentFrameDisplay_Rect = frames[m_currentIndex];
				m_changeTime = m_currentTime + (m_spriteAnimationFrequency);
				m_currentIndex++;
				if (m_currentIndex == frames.size() - 0)
				{
					m_currentIndex = 0;
				}
			}
		}
	}

	void SpriteAnimation::SetCurrentFrame(const Uint16& index) {
		m_currentIndex = index;
		if (frames.size() < index)
		{
			std::cerr << "Wrong Frame Number " << std::endl;
			m_currentIndex = 0;
			currentFrameDisplay_Rect = { 0, 0 , imageSurface->w , imageSurface->h };
		}
		else {
			m_currentIndex = index;
			currentFrameDisplay_Rect = frames[index];
		}
	}

	void SpriteAnimation::SetPivot(const Pivot& pivot) {
		this->pivot = pivot;
		if (this->pivot == Pivot::CENTER)
		{
			destination_Rect = { (int)m_position.x - (int)(m_size.x / 2), (int)m_position.y - (int)(m_size.y / 2) , (int)m_size.x , (int)m_size.y };
		}
		else if (this->pivot == Pivot::TOP_LEFT) {
			destination_Rect = { (int)m_position.x, (int)m_position.y , (int)m_size.x , (int)m_size.y };
		}
	}

	void SpriteAnimation::Play(SpriteAnimation::Animation_Mode animMode) {
		playAnim = true;
		//	m_currentTime = m_changeTime + m_spriteAnimationFrequency;
		m_changeTime = m_currentTime + m_spriteAnimationFrequency;
	}

	SpriteAnimation::~SpriteAnimation()
	{
		SDL_FreeSurface(imageSurface);
		SDL_DestroyTexture(texture);
	}
}
