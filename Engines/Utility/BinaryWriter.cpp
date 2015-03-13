//#include "StdAfx.h"

#include "BinaryWriter.h"
#include "StringUtil.h"
#include "string.h"

using namespace CR::Utility;

/*!
	The file specified will be opened and its previous contents replaced. The file will be
	automaticly closed when the BinaryWriter is destroyed. By default compression is turned off.
*/
BinaryWriter::BinaryWriter(const std::wstring &fileName) :
			  compressing(false),compressStream(NULL)
{
	stream.open(Convert()(fileName).c_str(),std::ios::out | std::ios::binary);
}

BinaryWriter::~BinaryWriter(void)
{
	if(compressing)
	{
		FinalizeCompress();
		FlushCompressed();
	}
	stream.close();
}

void BinaryWriter::CompressingMode(bool compressing)
{
	/*if(!this->compressing && compressing)
	{

		if(compressStream != NULL)
			delete compressStream;
		compressStream = new z_stream();
		memset(compressStream,0,sizeof(z_streamp));
		compressStream->data_type = Z_BINARY;
		memset(compressBuffer,0,COMPRESS_BUFFER_SIZE);
		compressStream->avail_out = COMPRESS_BUFFER_SIZE;
		compressStream->next_out = static_cast<Bytef*>(compressBuffer);
		deflateInit(compressStream,Z_DEFAULT_COMPRESSION);	
	}
	else if(this->compressing && !compressing)
	{
		while(deflate(compressStream,Z_FINISH) != Z_STREAM_END)
			FlushCompressed();

		deflateEnd(compressStream);
		FlushCompressed();
		if(compressStream != NULL)
		{
			delete compressStream;					
			compressStream = NULL;
		}
	}
	this->compressing = compressing;*/
}

/*!
	Writes the data out unaltered. Any information needed to recover the data(i.e. its length)
	must be written out manually.
*/
void BinaryWriter::Write(char* data,int size)
{
	/*if(compressing)
	{
		compressStream->avail_in = size;
		compressStream->next_in = reinterpret_cast<Bytef*>(data);
		while(compressStream->avail_in > 0)
		{
			if(compressStream->avail_out == 0)
				FlushCompressed();
		
			deflate(compressStream,Z_NO_FLUSH);
		}
	}
	else*/
		stream.rdbuf()->sputn(data,size);
}

/*!
	Writes a length prefixed string out the binary file. The length is written first
	to make reading the string back easier. the length is written out in variable length format.
	The least signifigant "byts" is written first. only the lower 7 bits of each byte are actually
	part of the length though. The most signifigant bit signals wether or not there is another byte
	that needs to be read for the length. This makes it effecient at storing short strings as well as
	long strings. BinaryWriter only supports unicode strings. Null terminating characters are not saved out.
*/
BinaryWriter& BinaryWriter::operator<<(const std::wstring &data)
{
	unsigned long length = static_cast<unsigned long>(data.length());
	while(length > 0)
	{
		unsigned char lengthSegment = static_cast<unsigned char>(length & 0x7f);
		length = length >> 7;
		if(length > 0)
			lengthSegment |= 0x80;
		(*this) << lengthSegment;
	}
	Write((char*)data.c_str(),static_cast<int>(data.length()*sizeof(wchar_t)));
	return *this;
}

void BinaryWriter::FlushCompressed()
{
	stream.rdbuf()->sputn(reinterpret_cast<char*>(compressBuffer),COMPRESS_BUFFER_SIZE-compressStream->avail_out);
	compressStream->avail_out = COMPRESS_BUFFER_SIZE;
	compressStream->next_out = compressBuffer;
}

void BinaryWriter::FinalizeCompress()
{
	/*deflate(compressStream,Z_FULL_FLUSH);
	while(compressStream->avail_out == 0)
	{
		FlushCompressed();
		deflate(compressStream,Z_FULL_FLUSH);
	}*/
}
