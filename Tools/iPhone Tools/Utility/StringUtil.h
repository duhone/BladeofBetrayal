#pragma once
#include<string>
#include "FunctionObjects.h"

namespace Syntax
{
	namespace Utility
	{
		struct UnicodeToAscii
		{
			char operator()(wchar_t _char)
			{
				char result;
				wctomb(&result,_char);
				return result;
			}
		};

		std::string Convert(const std::wstring &_original)
		{
			std::string result;
			result.resize(_original.size());
			Transform(_original,result,UnicodeToAscii());
			return result;
		}
	}
}

