#pragma once
#ifndef _MATHUTILITIES_H_
#define _MATHUTILITIES_H_

#include <cstdlib>

namespace Engine
{
	namespace Math
	{
		float DegreesToRadians(float angleInRadians);
		float RadiansToDegrees(float angleInDegrees);

		template<typename T>
		T RandomInRange(T min, T max)
		{
			return min + (max - min) * (rand() / static_cast<T>(RAND_MAX));
		}
	}
}

#endif