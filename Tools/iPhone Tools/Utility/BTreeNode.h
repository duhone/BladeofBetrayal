#pragma once
#include<hash_map>

namespace Syntax
{
	namespace Utility
	{
		template<class T,class S>
		class BTreeNode
		{
			typedef stdext::hash_map<T,BTreeNode<T,S>* > BTreeChildren;

		public:
			BTreeNode()
			{

			}
			BTreeNode(const T& key,const S& value)
			{
				this->key = key;
				this->value = &value;
			}
			~BTreeNode(void) {};
			unsigned long ChildCount() { return children.size();}
			S* GetChild(const std::vector<T> &key,unsigned int depth)
			{
				BTreeChildren::iterator iterator = children.find(key[depth]);
				if(iterator == children.end())
					return NULL;
				else
				{
					return iterator->GetChild(key,depth+1);
				}
			}
		private:
			T key;
			S* value;
			stdext::hash_map<T,BTreeNode<T,S>* > children;
		};
	}
}
