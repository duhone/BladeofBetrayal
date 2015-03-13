#pragma once
#include "BinaryWriter.h"

namespace Syntax
{
	namespace Utility
	{
		//!BinaryWriter Function object. For making the BinaryWriter easy to use with stl algorithms.
		/*!
			Usefull for saving on typing when you need to write out a collection of objects. For use with for_each or
			other stl algorithms. The entrys in your stl container must be directly writable to the BinaryWriter.

			Example:
			\verbatim
			BinaryWriter testFile(L"test.tst");
			vector<wstring> strings;
			//populate the vector with a bunch of strings.
			//instead of writing a loop to output those strings, you can use for_each and this Functor.

			//will write out all the strings to the file
			for_each(strings.begin(),string.end(),BinaryWriterFO(testFile));

			//file closed with testFile goes out of scope.
			\endverbatim
		*/
		class BinaryWriterFO
		{
		public:
			BinaryWriterFO(BinaryWriter &writer) : writer(writer) {}
			~BinaryWriterFO(void){}
			template<class T>
			void operator()(const T &data) {writer << data;}
		private:
			BinaryWriter &writer;
		};
	}
}
