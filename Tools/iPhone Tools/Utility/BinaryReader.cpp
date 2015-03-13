#include "StdAfx.h"
#include "BinaryReader.h"

using namespace std;
using namespace Syntax::Utility;
using namespace boost;

BinaryReader::BinaryReader(const wstring &fileName) :
			  compressing(false),compressBuffer(NULL),
			  compressStream(NULL)
{
	stream.open(fileName.c_str(),std::ios::in | std::ios::binary);
}

BinaryReader::~BinaryReader(void)
{
	if(compressBuffer != NULL)
		delete[] compressBuffer;
	stream.close();
}

void BinaryReader::CompressingMode(bool compressing,unsigned int compresedSize)
{
	if(!this->compressing && compressing)
	{

		if(compressStream != NULL)
			delete compressStream;
		compressStream = new z_stream();
		ZeroMemory(compressStream,sizeof(z_streamp));
		compressStream->data_type = Z_BINARY;
		if(compressBuffer != NULL)
			delete[] compressBuffer;
		compressBuffer = new char[compresedSize];
		ZeroMemory(compressBuffer,compresedSize);
		compressStream->avail_in = compresedSize;
		compressStream->next_in = reinterpret_cast<Bytef*>(compressBuffer);
		stream.rdbuf()->sgetn(compressBuffer,compresedSize);
		inflateInit(compressStream);	
	}
	else if(this->compressing && !compressing)
	{
		inflateEnd(compressStream);
		if(compressStream != NULL)
		{
			delete compressStream;
			compressStream = NULL;
		}
		if(compressBuffer != NULL)
		{
			delete[] compressBuffer;
			compressBuffer = NULL;
		}
	}
	this->compressing = compressing;
}

/*!
	Writes the data out unaltered. Any information needed to recover the data(i.e. its length)
	must be written out manually.
*/
void BinaryReader::Read(char* data,int size)
{
	if(compressing)
	{
		compressStream->avail_out = size;
		compressStream->next_out = reinterpret_cast<Bytef*>(data);
		while(compressStream->avail_out > 0)
		{
			inflate(compressStream,Z_SYNC_FLUSH);
		}
	}
	else
		stream.rdbuf()->sgetn(data,size);
}

/*!
	Writes a length prefixed string out the binary file. The length is written first
	to make reading the string back easier. the length is written out in variable length format.
	The least signifigant "byts" is written first. only the lower 7 bits of each byte are actually
	part of the length though. The most signifigant bit signals wether or not there is another byte
	that needs to be read for the length. This makes it effecient at storing short strings as well as
	long strings. BinaryWriter only supports unicode strings. Null terminating characters are not saved out.
*/
BinaryReader& BinaryReader::operator>>(wstring &data)
{
	unsigned long length = 0;
	unsigned char lengthSegment;
	bool more = true;
	unsigned long shiftAmount = 0;
	while(more)
	{
		(*this) >> lengthSegment;
		more = (lengthSegment & 0x80) != 0;
		length |= static_cast<unsigned long>(lengthSegment) << shiftAmount;
		shiftAmount += 7;
	}
	data.clear();
	scoped_array<wchar_t> tempString(new wchar_t[length+1]);
	Read(reinterpret_cast<char*>(tempString.get()),length*sizeof(wchar_t));
	tempString[length] = 0;
	data += tempString.get();
	return *this;
}