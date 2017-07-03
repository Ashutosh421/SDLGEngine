#pragma once
#include "../Maths/Vector.h"

using namespace AREngine::CoolMath;
namespace AREngine {
	class Camera
	{
	private:
		static Vector2 m_position;

	public:
		static void SetPosition(const Vector2&);
		static const Vector2& GetPosition();
	};
}

