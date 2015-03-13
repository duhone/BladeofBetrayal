/*
 *  ClassFactory.h
 *  Steph
 *
 *  Created by Eric Duhon on 4/14/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once

#include <boost/tr1/tr1/unordered_map>
#include "FunctionObjects.h"
#include "Singleton.h"
#include <boost/tr1/tr1/functional>

namespace CR
{
	namespace Utility
	{
		template<class Interface,class Key>
		class ClassFactory
		{
			friend class Singleton<ClassFactory>;
			typedef std::tr1::function<Interface* ()> Creater;
		public:
			bool RegisterCreater(Key _key,Creater _creater)
			{
				m_creaters.insert(std::make_pair(_key,_creater));
				return true;
			}
			Interface* Create(Key _key)
			{
				typename std::tr1::unordered_map<Key,Creater>::const_iterator iterator = m_creaters.find(_key);
				if(iterator == m_creaters.end())
					return NULL;
				else
					return (iterator->second)();
			}

		private:
			ClassFactory() {}
			ClassFactory(ClassFactory &_other);
			virtual ~ClassFactory() {}
			std::tr1::unordered_map<Key,Creater> m_creaters;
		};
		
		/*example use
		typedef Singleton<ClassFactory<IShape,int> > sahapeFactory;
		//use anonomous namespace so this part isnt accesable. and use const bool trick to register your creater 
		 
		 */
	}
}