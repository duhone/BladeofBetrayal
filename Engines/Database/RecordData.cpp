#include "RecordData.h"
#include "../Utility/BinaryReader.h"
#include "../Utility/ISerializable.h"

using namespace CR;
using namespace CR::Utility;
using namespace CR::Database;

RecordData::RecordData(BinaryReader *reader)
{
	this->reader = reader;
	reader->Lock();
}

RecordData::~RecordData(void)
{
	reader->UnLock();
}

/*bool RecordData::CompressingMode() const
{
	return reader->CompressingMode();
}

void RecordData::CompressingMode(bool compressing,unsigned int compresedSize)
{
	reader->CompressingMode(compressing,compresedSize);
}*/

void RecordData::Read(char* data,int size)
{
	reader->Read(data,size);
}
