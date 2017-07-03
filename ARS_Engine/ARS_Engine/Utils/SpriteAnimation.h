#pragma once
#include <string>
#include <SDL.h>
#include <vector>
#include <SDL_mixer.h>
#include "TextureResource.h"
#include "../Maths/Vector.h"
#include "../Utils/Time.h"
#include "Texture.h"

using namespace AREngine::CoolMath;

namespace AREngine {

	class SpriteAnimation
	{
	public:
		enum  Animation_Mode
		{
			ONCE,
			LOOP
		};

	private:
		SDL_Surface* imageSurface;
		std::vector <SDL_Rect> frames;
		bool active;
		bool debug;

		SDL_Rect currentFrameDisplay_Rect;
		SDL_Rect destination_Rect;

		Vector2 m_size;
		Pivot pivot;
		float m_angle;
		Uint16 m_currentIndex;
		Animation_Mode m_animationMode;
		bool playAnim = false;

		float m_currentTime = 0;
		float m_changeTime = 0;
		float m_spriteAnimationFrequency = 0.1f;

		//Kinematics Motion
		Vector2 m_position;
		Vector2 m_velocity;
		Vector2 m_accelertion;
		float m_gravity;
		float m_mass;

		bool m_activateGravity = false;

	public:
		SDL_Texture* texture;
		SpriteAnimation(std::string, SDL_Renderer*);

		void AddFrame(const int&, const int&, const int&, const int&);
		void Play(Animation_Mode animationMode);
		void Update(SDL_Renderer*);
		void SetCurrentFrame(const Uint16& index);
		void SetGravity(const float& gravity);
		void SetVelocity(const Vector2& velocity);
		void SetAcceleration(const Vector2& acceleration);
		void SetMass(const float& mass);
		void ActivateGravity(const bool& activate);

		const float& Mass();

		inline void SetAnimationFrequency(const float& frequency) {
			this->m_spriteAnimationFrequency = frequency;
		}

		inline const float& GetAnimationFrequency() {
			return this->m_spriteAnimationFrequency;
		}

		inline const int& TotalFrames() const {
			return this->frames.size();
		}

		inline const bool& Is_Active() const {
			return active;
		}

		inline void SetActive(const bool& val) {
			this->active = val;
		}

		inline void SetDebug(const bool& debug) {
			this->debug = debug;
			//std::cout << "Sprite ANimation debug to " << debug
		}

		inline void SetSize(const Vector2& size) {
			this->m_size = size;
			destination_Rect = { (int)m_position.x, (int)m_position.y , (int)m_size.x , (int)m_size.y };
			if (pivot == Pivot::CENTER)
			{
				destination_Rect = { (int)m_position.x - (int)(m_size.x / 2), (int)m_position.y - (int)(m_size.y / 2) , (int)m_size.x , (int)m_size.y };
			}
		}

		inline const Vector2& Size() const {
			return this->m_size;
		}

		inline void SetPosition(const Vector2& pos) {
			this->m_position = pos;
			destination_Rect = { (int)m_position.x, (int)m_position.y , (int)m_size.x , (int)m_size.y };
			if (pivot == Pivot::CENTER)
			{
				destination_Rect = { (int)m_position.x - (int)(m_size.x / 2), (int)m_position.y - (int)(m_size.y / 2) , (int)m_size.x , (int)m_size.y };
			}
		}

		inline const Vector2& GetPosition() const {
			return this->m_position;
		}

		void SetPivot(const Pivot& pivot);

		inline const Pivot& CheckPivot() const {
			return pivot;
		}

		inline void SetAngle(const float& angle) {
			this->m_angle = angle;
		}

		inline const float& GetAngle() const {
			return this->m_angle;
		}

		~SpriteAnimation();
	};
}

