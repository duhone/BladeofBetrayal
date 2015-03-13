#pragma once
//#include "Windows.h"
//#include <fstream>
//#ifdef WIN32
//#include "..\..\thirdparty\zlib\zlib.h"
//#else
//#include "zlib.h"
//#endif
#include "CriticalSection.h"
#include "ISerializable.h"
#include <stdio.h>
#include<string>

namespace CR
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
			//bool CompressingMode() { return compressing; }
			//! Set whether to compress any future data sent to the writer.
			//void CompressingMode(bool compressing,unsigned int compresedSize);
			//! Get the current file position.
			//long long Position() { return stream.tellg().seekpos();}
			//long long Position() { return stream.tellg();}
			long Position() { return ftell(m_file);}
			//! Sets the current file position. Always relative to the begining of the file.
			//void Position(long long position) {stream.seekg(std::streampos(static_cast<std::streamoff>(position)));}
			void Position(long position) {fseek(m_file,position,SEEK_SET);}
			//! Changes the file position by the provided offset. Negative numbers go backwards in the file. Relative to current position.
			//void Seek(long offset) {stream.seekg(offset,std::ios::cur);}
			void Seek(long offset) {fseek(m_file,offset,SEEK_CUR);}
			//! Writes binary data out to the file.
			void Read(char* data,int size);
			
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
			//! Reads a serializable object by reference.
			BinaryReader& operator>>(ISerializable &data) { data.DeSerialize(*this); return *this;}
			//! Reads a serializable object by pointer.
			BinaryReader& operator>>(ISerializable *data) { data->DeSerialize(*this); return *this;}
		private:
			BinaryReader(const BinaryReader&);
			void operator=(const BinaryReader&);
			FILE *m_file;
			//std::ifstream stream;
			//bool compressing;
			//z_streamp compressStream;
			//char *compressBuffer;
			CR::Utility::CriticalSection section;
		};
	}
}
