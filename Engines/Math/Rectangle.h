#pragma once
#include <algorithm>

namespace CR
{
	namespace Math
	{
		template<class T>
		class Rectangle
		{
		public:	
			Rectangle(void)	: top(0), left(0), width(0), height(0) {}
			Rectangle(T _top, T _left, T _width, T _height)	:
				top(_top), left(_left), width(_width), height(_height) {}
			~Rectangle(void) {}
			T Top() const {return top;}
			void Top(T _top) { top = _top;}
			T Left() const {return left;}
			void Left(T _left) { left = _left;}
			T Width() const {return width;}
			void Width(T _width) { width = _width;}
			T Height() const {return height;}
			void Height(T _height) { height = _height;}
			T Bottom() const {return top + height;}
			T Right() const {return left + width;}
			void Clamp(T _left,T _top,T _width,T _height)
			{
				left = max(left,_left);
				top = max(top,_top);
				width = min(left+width,left+_width)-left;
				height = min(top+height,top+_height)-top;
			}
		private:
			T top;
			T left;
			T width;
			T height;
		};

		typedef Rectangle<double> RectangleD;
		typedef Rectangle<float> RectangleF;
		typedef Rectangle<int> RectangleI;
	}
}
