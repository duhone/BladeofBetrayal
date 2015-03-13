#pragma once
#include<string>
#ifdef WIN32
#include<functional>
#else
//#include<tr1/functional>
#endif
namespace CR
{
	namespace Utility
	{
		class Guid
		{
		public:
			Guid(unsigned long _data1,unsigned long _data2,
				unsigned long _data3,unsigned long _data4)
			{
				data[0] = _data1;
				data[1] = _data2;
				data[2] = _data3;
				data[3] = _data4;
			}
			Guid(const Guid &_other)
			{
				(*this) = _other;
			}
			Guid& operator=(const Guid &_other)
			{
				data[0] = _other.data[0];
				data[1] = _other.data[1];
				data[2] = _other.data[2];
				data[3] = _other.data[3];
				return *this;
			}
			Guid()
			{
				data[0] = 0;
				data[1] = 0;
				data[2] = 0;
				data[3] = 0;
			}
			Guid(const std::wstring &_data)
			{
				Set(_data);
			}
			bool operator==(const Guid &_other) const
			{
				if(data[0] == _other.data[0] && data[1] == _other.data[1] &&
					data[2] == _other.data[2] && data[3] == _other.data[3])
					return true;
				else
					return false;
			}
			static Guid Null()
			{
				static Guid null = Guid(0,0,0,0);
				return null;
			}
			bool IsNull() const
			{
				if(data[0] == 0 && data[1] == 0 && data[2] == 0 && data[3] == 0)
					return true;
				else 
					return false;
			}
			void Set(const std::wstring &_data)
			{
				data[0] = data[1] = data[2] = data[3] = 0;
				int count = 0;
				std::wstring::const_iterator iterator = _data.begin();
				while(iterator != _data.end())
				{
					int index = (count&0x0ff8)>>3;
					if((*iterator) >= 48 && (*iterator) <= 57)
					{
						data[index] = (data[index] << 4)+((*iterator)-48);
						count++;
					}
					if((*iterator) >= 65 && (*iterator) <= 71)
					{
						data[index] = (data[index] << 4)+((*iterator)-55);
						count++;
					}
					if((*iterator) >= 97 && (*iterator) <= 102)
					{
						data[index] = (data[index] << 4)+((*iterator)-87);
						count++;
					}
					iterator++;
				}
			}
			unsigned long Data1() const {return data[0];}
			unsigned long Data2() const {return data[1];}
			unsigned long Data3() const {return data[2];}
			unsigned long Data4() const {return data[3];}
			unsigned long operator[](int _index) const
			{
				return data[_index];
			}
		bool operator<(const Guid &_other) const
		{
			for(int i = 0;i < 4;++i)
			{
				if(data[i]<_other[i])
					return true;
				if(data[i]>_other[i])
					return false;
			}
			return false;
		}
		private:
			unsigned long data[4];
		};
		
		//probably a better hash available.
		struct GuidHash
		{
			std::size_t operator()(const CR::Utility::Guid& _guid) const
			{
				return _guid.Data1() + _guid.Data2() + _guid.Data3() + _guid.Data4();
			}
			
		};
		//std::size_t hash_value(const Guid &_guid);		
	}
}