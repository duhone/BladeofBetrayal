#pragma once
#include "Windows.h"
#include <fstream>
#include "zlib.h"
#include "CriticalSection.h"
#include "ISerializable.h"

namespace Syntax
{
	namespace Utility
	{
		class BinaryReader
		{
		public:
			BinaryReader(const std::wstring &fileName);
			~BinaryReader(void);
			//! Lock this Binary reader. Other threads that call Lock will be blocked until initial thread calls UnLock
			void Lock() {section.Enter();}
			//!Unlock this reader. 1 thread waiting in the Lock call will be allowed to continue.
			void UnLock() {section.Leave();}
			//! Returns true if currently compressing.
			bool CompressingMode() { return compressing; }
			//! Set whether to compress any future data sent to the writer.
			void CompressingMode(bool compressing,unsigned int compresedSize);
			//! Get the current file position.
			long long Position() { return stream.tellg().seekpos();}
			//! Sets the current file position. Always relative to the begining of the file.
			void Position(long long position) {stream.seekg(std::streampos(static_cast<std::streamoff>(position)));}
			//! Changes the file position by the provided offset. Negative numbers go backwards in the file. Relative to current position.
			void Seek(long offset) {stream.seekg(offset,std::ios::cur);}
			//! Writes binary data out to the file.
			void Read(char* data,int size);
			/*//! Reads a bool out to the file.
			BinaryReader& operator>>(bool &data) {Read((char*)&data,sizeof(bool)); return *this;}
			//! Reads a char out to the file.
			BinaryReader& operator>>(char &data) {Read((char*)&data,sizeof(char)); return *this;}
			//! Reads a short out to the file.
			BinaryReader& operator>>(short &data) {Read((char*)&data,sizeof(short)); return *this;}
			//! Reads a long out to the file.
			BinaryReader& operator>>(long &data) {Read((char*)&data,sizeof(long)); return *this;}
			//! Reads a long long out to the file.
			BinaryReader& operator>>(long long &data) {Read((char*)&data,sizeof(long long)); return *this;}
			//! Reads a float out to the file.
			BinaryReader& operator>>(float &data) {Read((char*)&data,sizeof(float)); return *this;}
			//! Reads a double out to the file.
			BinaryReader& operator>>(double &data) {Read((char*)&data,sizeof(double)); return *this;}
			//! Reads a unsigned char out to the file.
			BinaryReader& operator>>(unsigned char &data) {Read((char*)&data,sizeof(unsigned char)); return *this;}
			//! Reads a unsigned short out to the file.
			BinaryReader& operator>>(unsigned short &data) {Read((char*)&data,sizeof(unsigned short)); return *this;}
			//! Reads a unsigned long out to the file.
			BinaryReader& operator>>(unsigned long &data) {Read((char*)&data,sizeof(unsigned long)); return *this;}
			//! Reads a unsigned long long out to the file.
			BinaryReader& operator>>(unsigned long long &data) {Read((char*)&data,sizeof(unsigned long long)); return *this;}
			*/
			template<class T>
			BinaryReader& operator>>(T &data) {Read((char*)&data,sizeof(T)); return *this;}
			
			//! Reads a wstring out to the file.
			BinaryReader& operator>>(std::wstring &data);
			//! Reads a pair<wstring,wstring> out to the file. Convenience function. Just writes the 2 strings out one after the other.
			template<class T,class S>
			BinaryReader& operator>>(std::pair<T,S> &data)
			{
				(*this) >> data.first >> data.second;
				return *this;
			}
			////! Reads a Vector4F out to the file.
			//BinaryReader& operator>>(Syntax::Math::Vector4F &data) {Read((char*)&data,sizeof(Syntax::Math::Vector4F)); return *this;}
			//! Reads a serializable object by reference.
			BinaryReader& operator>>(ISerializable &data) { data.DeSerialize(*this); return *this;}
			//! Reads a serializable object by pointer.
			BinaryReader& operator>>(ISerializable *data) { data->DeSerialize(*this); return *this;}
		private:
			BinaryReader(const BinaryReader&);
			void operator=(const BinaryReader&);
			std::ifstream stream;
			bool compressing;
			z_streamp compressStream;
			char *compressBuffer;
			Syntax::Utility::Threading::CriticalSection section;
		};
	}
}
