#pragma once
#include "BTreeNode.h"

namespace Syntax
{
	namespace Utility
	{
		template<class T,class S>
		class BTree
		{
		public:
			BTree(void) {};
			~BTree(void) {};
			S* Find(const std::vector<T> &key)
			{
				return head.GetChild(key,0);
			}
			void Add(const std::vector<T> &key,const S &value)
			{

			}
		private:
			BTreeNode<T,S> head;
		};
	}
}
