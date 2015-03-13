#pragma once
#include "database.h"
//#include "tr1/memory"
#include <memory>
//#include <tr1/unordered_map>

namespace CR
{
	namespace Database
	{	
		class DatabaseImpl;

		class Record :
			public CR::Database::IRecord
		{
		public:
			Record(CR::Utility::Guid &id, long long length, CR::Utility::BinaryReader &reader,DatabaseImpl *_database);
			virtual ~Record(void);
			virtual const CR::Utility::Guid& ID() const {return id;};
			virtual unsigned long ChildCount() const {return static_cast<unsigned long>(vchildren.size());};
			virtual const std::vector<const IRecord*>& GetChildren() const { return vchildren;}
			virtual const IRecord* const GetRecord(const CR::Utility::Guid& key) const;
			virtual std::auto_ptr<IRecordData> GetData() const;
		private:
			CR::Utility::Guid id;
			long long length;
			long long dataPosition;
			CR::Utility::BinaryReader &reader;
			std::vector<const IRecord*> vchildren;
			DatabaseImpl *database;
		};
	}
}
