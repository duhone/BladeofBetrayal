#pragma once

#include <string>
#include <vector>
#include <memory>
#include "../Utility/Singleton.h"
#include "../Utility/BinaryReader.h"
//#include "tr1/memory"
#include "../Math/Vector.h"
#include "../Math/Rectangle.h"
#include "../Math/Color.h"
#include "../Utility/Guid.h"

namespace CR
{
	namespace Database
	{
		class ISerializable;

		class IRecordData
		{
		public:
			virtual ~IRecordData() {};
			//! Returns true if currently compressing.
			//virtual bool CompressingMode() const = 0;
			//! Set whether to compress any future data sent to the writer.
			//virtual void CompressingMode(bool compressing,unsigned int compresedSize) = 0;
			//! Writes binary data out to the file.
			virtual void Read(char* data,int size) = 0;
			//! Reads a bool out to the file.
			virtual IRecordData& operator>>(bool &data) = 0;
			//! Reads a char out to the file.
			virtual IRecordData& operator>>(char &data) = 0;
			//! Reads a short out to the file.
			virtual IRecordData& operator>>(short &data) = 0;
			//! Reads a long out to the file.
			virtual IRecordData& operator>>(long &data) = 0;
			//! Reads a long long out to the file.
			virtual IRecordData& operator>>(long long &data) = 0;
			//! Reads a float out to the file.
			virtual IRecordData& operator>>(float &data) = 0;
			//! Reads a double out to the file.
			virtual IRecordData& operator>>(double &data) = 0;
			//! Reads a unsigned char out to the file.
			virtual IRecordData& operator>>(unsigned char &data) = 0;
			//! Reads a unsigned short out to the file.
			virtual IRecordData& operator>>(unsigned short &data) = 0;
			//! Reads a unsigned long out to the file.
			virtual IRecordData& operator>>(unsigned long &data) = 0;
			//! Reads a unsigned long long out to the file.
			virtual IRecordData& operator>>(unsigned long long &data) = 0;
			//! Reads a wstring out to the file.
			virtual IRecordData& operator>>(std::wstring &data) = 0;
			//! Reads a pair<wstring,wstring> out to the file. Convenience function. Just writes the 2 strings out one after the other.
			virtual IRecordData& operator>>(std::pair<std::wstring,std::wstring> &data) = 0;
			//! Reads a ISerializable out to the file.
			virtual IRecordData& operator>>(CR::Utility::ISerializable &data) = 0;
			//! Reads a ISerializable out to the file.
			virtual IRecordData& operator>>(CR::Utility::ISerializable *data) = 0;
			//! Reads a Vector4F out to the file.
			virtual IRecordData& operator>>(CR::Math::Vector4F &data) = 0;
			//! Reads a RectangleI out to the file.
			virtual IRecordData& operator>>(CR::Math::RectangleI &data) = 0;
			//! Reads a Color32 out to the file.
			virtual IRecordData& operator>>(CR::Math::Color32 &data) = 0;
			//! Reads a Guid out to the file.
			virtual IRecordData& operator>>(CR::Utility::Guid &data) = 0;
		protected:
			IRecordData() {};
			IRecordData(const IRecordData* arg) {};
			const IRecordData& operator=(const IRecordData& arg);
		};

		class IRecord
		{
		public:
			virtual const CR::Utility::Guid& ID() const = 0;
			virtual unsigned long ChildCount() const = 0;
			virtual const std::vector<const IRecord*>& GetChildren() const = 0;
			virtual const IRecord* const GetRecord(const CR::Utility::Guid& key) const = 0;
			virtual std::auto_ptr<IRecordData> GetData() const = 0;
		protected:
			IRecord() {};
			IRecord(const IRecord* other) {};
			const IRecord& operator=(const IRecord& arg);
			virtual ~IRecord() {};
		};

		class IDatabase
		{
		public:
			virtual const IRecord* const GetRoot() const = 0;
			// you should treat this as a const function. bug in gcc 4.0 tr1 implementation causes this not to compile
			//	if its a const function. fix this when that is fixed
			virtual const IRecord* const GetRecord(const CR::Utility::Guid &key) = 0;
			virtual void MergeFile(std::wstring fileName)= 0;
			virtual void Release() = 0;
		protected:
			IDatabase() {};
			IDatabase(const IDatabase* other) {};
			const IDatabase& operator=(const IDatabase& arg);
			virtual ~IDatabase() {};
		};

		class DatabaseFactory : public CR::Utility::Singleton<DatabaseFactory>
		{
			friend class CR::Utility::Singleton<DatabaseFactory>;
		public:
			IDatabase* CreateDatabase(const std::wstring& fileName);
		private:
			DatabaseFactory(void) {};
			virtual ~DatabaseFactory(void) {};
		};
	}
}
