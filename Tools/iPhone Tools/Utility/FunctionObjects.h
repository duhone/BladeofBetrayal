#pragma once
#include <map>
#include <hash_map>
#include <algorithm>
#include <boost/type_traits/is_pointer.hpp>

namespace Syntax
{
	namespace Utility
	{
		//! Delete Function object
		/*!
			Function object to delete a pointer. T must be a pointer type or this will fail.

			Example:
			\verbatim
			class MyClass;
			...
			vector<MyClass*> objects;
			//fill with data
			..
			//now i want to clear it, but want to delete all the objects first
			for_each(objects.begin(),objects.end(),DeleteFO());
			objects.clear();
			\endverbatim
		*/
		class DeleteFO
		{
		public:
			template<class T>
			void operator () (T arg)
			{
				delete arg;
			}
		};
		//! Delete Function object
		/*!
			Function object to delete a pointer. S must be a pointer type or this will fail.
			Used for map type containers. T is the key which is not deleted, and S is a pointer value

			Example:
			\verbatim
			class MyClass;
			...
			hash_map<string,MyClass*> objects;
			//fill with data
			..
			//now i want to clear it, but want to delete all the objects first
			for_each(objects.begin(),objects.end(),DeleteFO<string,MyClass*>());
			objects.clear();
			\endverbatim
		*/
		class DeleteFOPair
		{
		public:
			template<class T,class S>
			void operator () (std::pair<T,S> arg)
			{
				delete arg.second;
			}
		};
		//! Select 1st Function object
		/*!
			Function object to select the first element of a pair. 

			Example:
			\verbatim
			void print(string); ...

			class MyClass;
			...
			hash_map<string,MyClass*> objects;
			//fill with data
			..
			//now i want to call print for each element passing the key
			for_each(objects.begin(),objects.end(),print(Select1st()));
			objects.clear();
			\endverbatim
		*/
		template<class T,class S>
		class Select1st : public std::unary_function<std::pair<T,S>,T>
		{
		public:
			T operator () (std::pair<T,S> arg)
			{
				return arg.first;
			}
		};
		//! Select 2nd Function object
		/*!
			Function object to select the second element of a pair. 

			Example:
			\verbatim
			void print(string); ...

			class MyClass;
			...
			hash_map<string,MyClass*> objects;
			//fill with data
			..
			//now i want to call print for each element passing the value
			for_each(objects.begin(),objects.end(),print(Select2nd()));
			objects.clear();
			\endverbatim
		*/
		template<class T,class S>
		class Select2nd : public std::unary_function<std::pair<T,S>,S>
		{
		public:
			S operator () (std::pair<T,S> arg)
			{
				return arg.second;
			}
		};

		/*template<class T,class S>
		class SortBy1st : public std::binary_function<std::pair<T,S>,S>
		{
		public:
			bool operator () (std::pair<T,S> arg1,std::pair<T,S> arg2)
			{
				if(arg1.first < arg2.first)
					return true;
				else return false;
			}
		};*/

		template<class T,class S>
		class Pair2ndToVector : public std::unary_function<std::pair<T,S>,void>
		{
		public:
			Pair2ndToVector(std::vector<S> &list) : list(list) {}
			void operator () (std::pair<T,S> arg)
			{
				list.push_back(arg.second);
			}
		private:
			std::vector<S> &list;
		};

		template<class T,class F>
		void ForEach(T &list,F ftor)
		{
			std::for_each(list.begin(),list.end(),ftor);
		};

		template<class T,class S,class F>
		void Transform(T &src,S &dst,F ftor)
		{
			std::transform(src.begin(),src.end(),dst.begin(),ftor);
		};

		template<class F,class T,class S>
		class CallOn2ndInternal
		{
		public:
			CallOn2ndInternal(F ftor) {this->ftor = ftor;}
			void operator()(std::pair<T,S> _item)
			{
				//if(boost::is_pointer<S>())
					((_item.second)->*(ftor))();
				//else
				//	((_item.second).*(ftor))();
			}
		private:
			F ftor;
		};

		template<class F,class T,class S>
		void CallOn2nd(stdext::hash_map<T,S> &_container,F ftor)
		{
			CallOn2ndInternal<F,T,S> coi(ftor);
			ForEach(_container,coi);
		}

		template<class Key,class T>
		T* Find(const std::map<Key,T*> &_container,const Key &_key)
		{
			std::map<Key,T*>::const_iterator iterator = _container.find(_key);
			if(iterator == _container.end())
				return NULL;
			else
				return iterator->second;
		}

		template<class Key,class T>
		T* Find(const stdext::hash_map<Key,T*> &_container,const Key &_key)
		{
			stdext::hash_map<Key,T*>::const_iterator iterator = _container.find(_key);
			if(iterator == _container.end())
				return NULL;
			else
				return iterator->second;
		}
	}
}