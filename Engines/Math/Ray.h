#pragma once
#include "Point.h"
#include "Vector.h"

namespace CR
{
	namespace Math
	{		
		template<class T>
		class Ray
		{
		public:

			Ray(void)
			{
			}

			~Ray(void)
			{
			}
		private:
			Point<T> origin;
			Vector3<T> direction;
		};
	}
}
