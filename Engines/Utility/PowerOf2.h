#pragma once

namespace CR
{
	namespace Utility
	{
		template <unsigned short n>
		struct PowerOf2
		{
			static unsigned const Value = 2*PowerOf2<n-1>::Value;
		};

		template<>
		struct PowerOf2<1>
		{
			static unsigned const Value = 1;
		};

		template<>
		struct PowerOf2<0>
		{
			static unsigned const Value = 0;
		};
	}
}
