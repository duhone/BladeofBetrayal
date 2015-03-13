namespace Syntax
{
	namespace Utility
	{
		class Exception
		{
		public:
			Exception(const std::wstring& msg)
			{
				this->msg = msg;
			}
			const std::wstring& Message() const {return msg;}
		private:
			std::wstring msg;
		};

		class NotImplementedException : public Exception
		{
		public:
			NotImplementedException() : Exception(L"Not Implemented") {}
		};
	}
}