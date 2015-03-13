#pragma once
#include "database.h"
#include "Record.h"
//#include "ForwardDeclarations.h"
#include "../Utility/Guid.h"
#include "boost/tr1/tr1/unordered_map"
//#include <map>

namespace CR
{
	namespace Database
	{
		class DatabaseImpl :
			public CR::Database::IDatabase
		{
		public:
			DatabaseImpl(std::wstring fileName);
			virtual ~DatabaseImpl(void);
			virtual const IRecord* const GetRoot() const;
			virtual const IRecord* const GetRecord(const CR::Utility::Guid &key) ;
			virtual void MergeFile(std::wstring fileName);
			virtual void Release();
			void AddRecord(IRecord *_record) {records[_record->ID()] = _record;}
		private:
			Record *root;
			CR::Utility::BinaryReader *reader;
			std::tr1::unordered_map<CR::Utility::Guid,IRecord*,CR::Utility::GuidHash> records;
			//std::map<CR::Utility::Guid,IRecord*> records;
		};
	}
}
