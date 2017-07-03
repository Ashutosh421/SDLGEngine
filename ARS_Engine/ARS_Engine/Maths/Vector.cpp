#include "Vector.h"

namespace AREngine {
	namespace CoolMath {

		Vector2::Vector2() :x(0), y(0) {}

		Vector2::Vector2(float _x, float _y) : x(_x), y(_y) {}

		float Vector2::Magnitude() {
			return sqrtf(powf(x, 2) + powf(y, 2));
		}

		void Vector2::SetMagnitude(const float length) {
			float angle = this->GetAngle();

			this->x = cos(angle) * length;
			this->y = sin(angle) * length;
		}

		void Vector2::Normalize() {
			float magnitude = this->Magnitude();

			this->x /= magnitude;
			this->y /= magnitude;
		}

		void Vector2::SetAngle(const float& angle) {
			float magnitude = this->Magnitude();

			this->x = cos(angle) * magnitude;
			this->y = sin(angle) * magnitude;
		}

		float Vector2::GetAngle() {
			return atan2(this->y, this->x);
		}

		//Operations on Vectors
		const Vector2& Vector2::AddBy(const Vector2& other) {
			this->x += other.x;
			this->y += other.y;
			return *this;
		}

		const Vector2& Vector2::SubtractBy(const Vector2& other) {
			this->x -= other.x;
			this->y -= other.y;
			return *this;
		}

		const Vector2& Vector2::Multiply(const float& val) {
			this->x *= val;
			this->y *= val;
			return *this;
		}

		Vector2 Vector2::Add(const Vector2& vec1, const Vector2& vec2) {
			return Vector2((vec1.x + vec2.x), (vec1.y + vec2.y));
		}

		Vector2 Vector2::Subtract(const Vector2& vec1, const Vector2& vec2) {
			return Vector2((vec1.x - vec2.x), (vec1.y - vec2.y));
		}

		unsigned short Vector2::Distance(const Vector2& vec1, const Vector2& vec2) {
			return sqrtf(pow((vec2.x - vec1.x), 2) + pow((vec2.y - vec1.y), 2));
		}

		const Vector2& Vector2::operator+(const Vector2& other) {
			return this->AddBy(other);
		}

		const Vector2& Vector2::operator-(const Vector2& other) {
			return this->SubtractBy(other);
		}

		const Vector2 Vector2::operator*(const float& other) {
			Vector2 result;
			result.x = this->x * other;
			result.y = this->y * other;
			return result;
		}

		const Vector2& Vector2::operator+=(const Vector2& other) {
			return this->AddBy(other);
		}

		const Vector2& Vector2::operator-=(const Vector2& other) {
			return this->SubtractBy(other);
		}

		const Vector2& Vector2::operator*=(const float& val) {
			return this->Multiply(val);
		}

		std::ostream& operator<<(std::ostream& out, const Vector2& val) {
			return out << val.x << " , " << val.y;
		}
	}
}