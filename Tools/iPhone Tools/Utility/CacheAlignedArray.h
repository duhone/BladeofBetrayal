#pragma once
#include "PowerOf2.h"

namespace Syntax
{
	namespace Utility
	{
		const unsigned long CacheLineSize = PowerOf2<5>::Value;

		template<class T>
		class CacheAlignedArray
		{
		public:

			CacheAlignedArray() :realData(NULL), 
				alignedData(NULL) {}
			CacheAlignedArray(unsigned long size) :realData(NULL), 
				alignedData(NULL)
			{
				Init(size);
			}

			~CacheAlignedArray(void)
			{
				Free();
			}

			void Init(unsigned long size)
			{
				Free();
				realData = new T[size+CacheLineSize-1];
				unsigned int extra = reinterpret_cast<unsigned int>(realData)&(CacheLineSize-1);
				if(extra == 0)
					alignedData = realData;
				else
					alignedData = realData + (CacheLineSize-extra);
			}
			const T& operator[](int _index) const { return alignedData[_index];}
			T& operator[](int _index) {return alignedData[_index];}
			T* Get() {return alignedData;}
			const T* Get() const {return alignedData;}
		private:
			void Free()
			{
				if(realData != NULL)
					delete realData;
			}
			T *realData;
			T *alignedData;
		};

		
		template<class T>
		class CacheAlignedArray2D : public CacheAlignedArray<T>
		{
		public:
			CacheAlignedArray2D() : CacheAlignedArray() {}
			CacheAlignedArray2D(unsigned long _width, unsigned long _height) :CacheAlignedArray(_width*_height), 
				width(_width) {}
			void Init(unsigned long _width, unsigned long _height)
			{
				CacheAlignedArray::Init(_width*_height);
			}
			T& operator()(unsigned long _x,unsigned long _y) { return data[_y*width+_x];}
		private:
			unsigned long width;
		};
	}
}
