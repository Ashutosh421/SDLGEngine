#pragma once
#include <SDL.h>

namespace AREngine {
	struct Color
	{
		Uint8 r;
		Uint8 g;
		Uint8 b;
		Uint8 a;

		Color() :r(0), g(0), b(0), a(0) {

		}

		Color(Uint8 _r, Uint8 _g, Uint8 _b, Uint8 _a) :r(_r), g(_g), b(_b), a(_a)
		{

		}
	};
}