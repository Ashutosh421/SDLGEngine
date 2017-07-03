#include "Time.h"

namespace AREngine {
	float Time::m_currentTime = 0;
	float Time::m_prevTime = 0;
	float Time::time = 0;
	float Time::deltaTime = 0;
	float Time::deltaTimeInSeconds = 0;
	float Time::timeInSeconds = 0;

	Time::Time()
	{
		m_currentTime = 0;
		m_prevTime = 0;
		time = 0;
		deltaTime = 0;
		deltaTimeInSeconds = 0.001f;
		timeInSeconds = 0;
	}

	void Time::UpdateTime()
	{
		m_currentTime = SDL_GetTicks();
		deltaTimeInSeconds = m_currentTime - m_prevTime;
		deltaTime = deltaTimeInSeconds / 1000;
		m_prevTime = m_currentTime;

		timeInSeconds = SDL_GetTicks();
		time = timeInSeconds / 1000;
	}

	Time::~Time()
	{

	}
}