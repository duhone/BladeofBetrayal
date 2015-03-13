#pragma once

namespace CR
{
	namespace Math
	{
		template<class T>
		class Point
		{
		public:
			Point(void) : x(0), y(0), z(0) {}
			Point(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}
			~Point(void) {}
			T X() const {return x;}
			void X(T _x) {x=_x;}
			T Y() const {return y;}
			void Y(T _y) {y=_y;}
			T Z() const {return z;}
			void Z(T _z) {z=_z;}
		private:
			T x;
			T y;
			T z;
		};

		typedef Point<float> PointF;
		typedef Point<double> PointD;
		typedef Point<int> PointI;
	}
}
