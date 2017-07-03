#pragma once
#include <stdio.h>
#include <math.h>
#include <iostream>


namespace AREngine {
	/// A basic 2D Vector Maths
	namespace CoolMath {

		struct Vector2
		{
			float x;
			float y;

			Vector2();
			Vector2(float, float);

			float Magnitude();
			void SetMagnitude(const float length);

			void SetAngle(const float& angle);
			float GetAngle();

			void Normalize();

			//Operations on Vectors
			const Vector2& AddBy(const Vector2&);
			const Vector2& SubtractBy(const Vector2&);
			const Vector2& Multiply(const float&);

			Vector2 static Add(const Vector2& vec1, const Vector2& vec2);
			Vector2 static Subtract(const Vector2& vec1, const Vector2& vec2);
			unsigned short static Distance(const Vector2& vec1, const Vector2& vec2);

			const Vector2& operator+(const Vector2&);
			const Vector2& operator-(const Vector2&);
			const Vector2 operator*(const float&);

			const Vector2& operator+=(const Vector2&);
			const Vector2& operator-=(const Vector2&);
			const Vector2& operator*=(const float&);

			friend std::ostream& operator<<(std::ostream& out, const Vector2& val);
		};

	}
}

