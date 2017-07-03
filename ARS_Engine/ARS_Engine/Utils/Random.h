#pragma once
#include <random>
#include <iostream>

namespace AREngine {
	template <class T>
	class Random
	{
	public:
		static T Range(T, T);
	};

	template <class T>
	T Random<T>::Range(T min, T max) {
		//	std::cout << "Value of Min " << min << std::endl;
			//std::cout << "Value of Max " << max << std::endl;
		T totalNumbers = max - min;
		int x = (rand() % (int)(totalNumbers + 1) + (min));
		//std::cout << "Number generated is  " << x << std::endl;
		return x;
	}
}


