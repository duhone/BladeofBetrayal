#include<exception>

namespace CR
{
	namespace Utility
	{
		class NotImplementedException : public std::exception
		{
		public:
			virtual const char* what() const throw()
			{
				return "Not Implemented";
			}
		};
	}
}