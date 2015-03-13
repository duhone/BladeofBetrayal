#include "DatabaseImpl.h"
#include "../Utility/Exceptions.h"
#include "Record.h"
#include "../Utility/BinaryReader.h"

using namespace std;
using namespace std::tr1;
using namespace CR;
using namespace CR::Utility;
using namespace CR::Database;

DatabaseImpl::DatabaseImpl(std::wstring fileName)
{
	reader = new BinaryReader(fileName);
	Guid id;
	long long length;
	(*reader) >> id;
	(*reader) >> length;

	root = new Record(id,length,*reader,this);
	records[id] = root;
}

DatabaseImpl::~DatabaseImpl(void)
{
	delete root;
	delete reader;
	records.clear();
}

void DatabaseImpl::Release()
{
	delete this;
}

const IRecord* const DatabaseImpl::GetRoot() const
{
	return root;
}

const IRecord* const DatabaseImpl::GetRecord(const Guid& key) 
{
	unordered_map<Guid,IRecord*,GuidHash>::const_iterator iterator = records.find(key);
	//map<Guid,IRecord*>::const_iterator iterator = records.find(key);
	if(iterator == records.end())
		return NULL;
	return iterator->second;
}

void DatabaseImpl::MergeFile(std::wstring fileName)
{
	//throw NotImplementedException();
}
