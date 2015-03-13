#pragma once
#include "database.h"

namespace CR
{
	namespace Database
	{
		class RecordData :
			public CR::Database::IRecordData
		{
		public:
			RecordData(CR::Utility::BinaryReader *reader);
			virtual ~RecordData();
			//! Returns true if currently compressing.
			//virtual bool CompressingMode() const ;
			//! Set whether to compress any future data sent to the writer.
			//virtual void CompressingMode(bool compressing,unsigned int compresedSize);
			//! Writes binary data out to the file.
			virtual void Read(char* data,int size);
			template<class T>
			IRecordData& PassThrough(T &data);

			//! Reads a bool out to the file.
			virtual IRecordData& operator>>(bool &data) {return PassThrough(data);}
			//! Reads a char out to the file.
			virtual IRecordData& operator>>(char &data) {return PassThrough(data);}
			//! Reads a short out to the file.
			virtual IRecordData& operator>>(short &data) {return PassThrough(data);}
			//! Reads a long out to the file.
			virtual IRecordData& operator>>(long &data) {return PassThrough(data);}
			//! Reads a long long out to the file.
			virtual IRecordData& operator>>(long long &data) {return PassThrough(data);}
			//! Reads a float out to the file.
			virtual IRecordData& operator>>(float &data) {return PassThrough(data);}
			//! Reads a double out to the file.
			virtual IRecordData& operator>>(double &data) {return PassThrough(data);}
			//! Reads a unsigned char out to the file.
			virtual IRecordData& operator>>(unsigned char &data) {return PassThrough(data);}
			//! Reads a unsigned short out to the file.
			virtual IRecordData& operator>>(unsigned short &data) {return PassThrough(data);}
			//! Reads a unsigned long out to the file.
			virtual IRecordData& operator>>(unsigned long &data) {return PassThrough(data);}
			//! Reads a unsigned long long out to the file.
			virtual IRecordData& operator>>(unsigned long long &data) {return PassThrough(data);}
			//! Reads a wstring out to the file.
			virtual IRecordData& operator>>(std::wstring &data) {return PassThrough(data);}
			//! Reads a pair<wstring,wstring> out to the file. Convenience function. Just writes the 2 strings out one after the other.
			virtual IRecordData& operator>>(std::pair<std::wstring,std::wstring> &data) {return PassThrough(data);}
			//! Reads a ISerializable out to the file.
			virtual IRecordData& operator>>(CR::Utility::ISerializable &data) {return PassThrough(data);}
			//! Reads a ISerializable out to the file.
			virtual IRecordData& operator>>(CR::Utility::ISerializable *data) {return PassThrough(data);}
			//! Reads a Vector4F out to the file.
			virtual IRecordData& operator>>(CR::Math::Vector4F &data) {return PassThrough(data);}
			//! Reads a Guid out to the file.
			virtual IRecordData& operator>>(CR::Utility::Guid &data) {return PassThrough(data);}
			//! Reads a RectangleI out to the file.
			virtual IRecordData& operator>>(CR::Math::RectangleI &data) {return PassThrough(data);}
			//! Reads a Color32 out to the file.
			virtual IRecordData& operator>>(CR::Math::Color32 &data) {return PassThrough(data);}
			
		protected:
			RecordData(const RecordData* arg) {};
			const RecordData& operator=(const RecordData& arg);
		private:
			CR::Utility::BinaryReader *reader;
		};

		
		template<class T>
		IRecordData& RecordData::PassThrough(T &data)
		{
			reader->operator >>(data);
			return *this;
		}
	}
}
