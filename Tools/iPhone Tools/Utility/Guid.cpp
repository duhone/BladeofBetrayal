#include "StdAfx.h"
#include "Guid.h"

using namespace Syntax;
using namespace Syntax::Utility;

std::size_t Syntax::Utility::hash_value(const Syntax::Utility::Guid &_guid)
{
	std::size_t seed = 0;
	boost::hash_combine(seed, _guid.Data1());
	boost::hash_combine(seed, _guid.Data2());
	boost::hash_combine(seed, _guid.Data3());
	boost::hash_combine(seed, _guid.Data4());

	return seed;
}