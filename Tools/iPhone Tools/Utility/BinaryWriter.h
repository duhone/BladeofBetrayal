#pragma once
#include <fstream>
#include "zlib.h"
#include "ISerializable.h"

namespace Syntax
{
	namespace Utility
	{
		//!Used to make writing to binary files easier.
		/*!
			The BinaryWriter provides an interface similar to standard stl ostreams.
			However its << operators write out data in binary instead of text format.
			The Writer also supports zlib compression. 

			Example:
			\verbatim
			BinaryWriter testFile(L"test.tst");
			testFile << 5;
			testfile << L"Hello" << 15.6;
			char data[256];
			testFile.Write(data,256);
			//file closed with testFile goes out of scope.
			\endverbatim
		*/
		class BinaryWriter 
		{
		public:
			//! Constructs a new BinaryWriter using the file specified.
			BinaryWriter(const std::wstring &fileName);
			//! Closes the file.
			virtual ~BinaryWriter(void);
			//! Returns true if currently compressing.
			bool CompressingMode() { return compressing; }
			//! Set whether to compress any future data sent to the writer.
			void CompressingMode(bool compressing);
			//! Get the current file position.
			long long Position() { return stream.tellp().seekpos();}
			//! Sets the current file position. Always relative to the begining of the file.
			void Position(long long position) {stream.seekp(std::streampos(static_cast<std::streamoff>(position)));}
			//! Changes the file position by the provided offset. Negative numbers go backwards in the file. Relative to current position.
			void Seek(long offset) {stream.seekp(offset,std::ios::cur);}
			//! Writes binary data out to the file.
			void Write(char* data,int size);			
			//! Writes a wstring out to the file.
			BinaryWriter& operator<<(const std::wstring &data);
			
			template<class T>
			BinaryWriter& operator<<(const T &data) {Write((char*)&data,sizeof(T)); return *this;}
			
			template<class T,class S>
			BinaryWriter& operator<<(const std::pair<T,S> &data)
			{
				(*this) << data.first << data.second;
				return *this;
			}
			//! Writes a serializable object by reference.
			BinaryWriter& operator<<(const ISerializable &data) { data.Serialize(*this);}
			//! Writes a serializable object by pointer.
			BinaryWriter& operator<<(const ISerializable* const data) { data->Serialize(*this);}
			
		private:
			BinaryWriter(const BinaryWriter&);
			void operator=(const BinaryWriter&);
			void FlushCompressed();
			void FinalizeCompress();
			static const int COMPRESS_BUFFER_SIZE = 4096;
			std::ofstream stream;
			bool compressing;
			z_streamp compressStream;
			unsigned char compressBuffer[COMPRESS_BUFFER_SIZE];
		};			
	}
}
