#include "StringUtil.h"

bool CR::Utility::CaseInsensitiveCompare(const std::wstring &s1,const std::wstring &s2)
{
	if(s1.length() != s2.length())
		return false;
	std::wstring::const_iterator iter1 = s1.begin();
	std::wstring::const_iterator iter2 = s2.begin();
	std::wstring::const_iterator end = s1.end();

	while(iter1 != end)
	{
		wchar_t c1 = *iter1;
		wchar_t c2 = *iter2;
		if(c1 >= 'A' && c1 <= 'Z')
			c1 += 'a'-'A';
		if(c2 >= 'A' && c2 <= 'Z')
			c2 += 'a'-'A';

		if(c1 != c2)
			return false;
		++iter1;++iter2;
	}
	return true;
}