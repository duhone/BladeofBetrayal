#pragma once

namespace CR
{
	namespace Math
	{		
		template<class T>
		class Vector3
		{
		public:
			Vector3(void) : x(0), y(0), z(0){}
			Vector3(T _x, T _y, T _z) : x(_x), y(_y), z(_z){}
			~Vector3(void) {}
			T X() const {return x;}
			void X(T _x) {x=_x;}
			T Y() const {return y;}
			void Y(T _y) {y=_y;}
			T Z() const {return z;}
			void Z(T _z) {z=_z;}
			void Set(T _x, T _y, T _z)
			{
				x = _x; y = _y; z= _z;
			}
		private:
			T x;
			T y;
			T z;
		};

		template<class T>
		float operator*(const Vector3<T> &_vec1,const Vector3<T> &_vec2)
		{
			return _vec1.X()*_vec2.X()+_vec1.Y()*_vec2.Y()+_vec1.Z()*_vec2.Z();
		}
		
		template<class T>
		Vector3<T> operator*(const Vector3<T> &_vec1,const T _arg)
		{
			return Vector3<T>(_vec1.X()*_arg,_vec1.Y()*_arg,_vec1.Z()*_arg);
		}
		
		template<class T>
		Vector3<T> operator*(const T _arg,const Vector3<T> &_vec1)
		{
			return _vec1*_arg;
		}
		
		template<class T>
		Vector3<T> operator+(const Vector3<T> &_vec1,const Vector3<T> &_vec2)
		{
			return Vector3<T>(_vec1.X()+_vec2.X(),_vec1.Y()+_vec2.Y(),_vec1.Z()+_vec2.Z());
		}
		
		template<class T>
		Vector3<T> operator-(const Vector3<T> &_vec1,const Vector3<T> &_vec2)
		{
			return Vector3<T>(_vec1.X()-_vec2.X(),_vec1.Y()-_vec2.Y(),_vec1.Z()-_vec2.Z());
		}
		
		template<class T>
		class Vector4
		{
		public:
			Vector4(void) : x(0), y(0), z(0), w(0) {}
			Vector4(T _x, T _y, T _z, T _w) : x(_x), y(_y), z(_z), w(_w) {}
			~Vector4(void) {}
			T X() const {return x;}
			void X(T _x) {x=_x;}
			T Y() const {return y;}
			void Y(T _y) {y=_y;}
			T Z() const {return z;}
			void Z(T _z) {z=_z;}
			T W() const {return w;}
			void W(T _w) {w=_w;}
		private:
			T x;
			T y;
			T z;
			T w;
		};
		
		template<class T>
		float operator*(const Vector4<T> &_vec1,const Vector4<T> &_vec2)
		{
			return _vec1.X()*_vec2.X()+_vec1.Y()*_vec2.Y()+_vec1.Z()*_vec2.Z()+_vec1.W()*_vec2.W();
		}

		typedef Vector3<float> Vector3F;
		typedef Vector3<double> Vector3D;
		typedef Vector3<int> Vector3I;
		typedef Vector4<float> Vector4F;
		typedef Vector4<double> Vector4D;
		typedef Vector4<int> Vector4I;
		//typedef Vector
	}
}
