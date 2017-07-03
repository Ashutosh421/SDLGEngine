#pragma once
#include <iostream>
#include <SDL.h>

namespace AREngine {
	class Time
	{
	private:
		static float m_currentTime;
		static float m_prevTime;

	public:
		static float time;
		static float timeInSeconds;
		static float deltaTime;
		static float deltaTimeInSeconds;

		Time();
		static void UpdateTime();
		~Time();
	};
}



