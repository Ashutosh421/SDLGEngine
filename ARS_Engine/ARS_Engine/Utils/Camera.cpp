#include "Camera.h"
namespace AREngine {
	Vector2 Camera::m_position;

	void Camera::SetPosition(const Vector2& val) {
		m_position = val;
	}

	const Vector2& Camera::GetPosition() {
		return m_position;
	}
}

