#pragma once
#include <streambuf>

class ZlibOutBufer : public std::streambuf
{
public:

	ZlibOutBufer(void)
	{
	}

	virtual ~ZlibOutBufer(void)
	{
	}

	virtual int_type overflow (int_type c)
	{
		if(c != EOF)
		{

		}
		return c;
	}
	virtual std::streamsize xsputn (const char*s,std::streamsize num)
	{

	}
};
