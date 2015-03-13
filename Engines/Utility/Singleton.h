#pragma once
#include "CriticalSection.h"
#include "AutoLock.h"
#include "stddef.h"

namespace CR
{
	namespace Utility
	{		
		//! Singleton base template class.
		/*!
			Derive from this class to create a Singleton class. The template parameter
			is the name of your derived class. Your derived class must be a friend of 
			this template. Friend classes are bad in general, but could not find another
			way to make this work. Make sure the constructor is private in your dervived
			class to insure no one can create an instance of it. You must have a no argument
			constructor. No other constructors will ever be called.

			This template is thread safe.

			Example:
			\verbatim
			class MyClass : public Syntax::Utility::Singleton<MyClass>
			{
				friend Syntax::Utility::Singleton<MyClass>;
			public:
				...
				void Test() ...
			private:
				MyClass();
				~MyClass();
			}

			MyClass::Instance().Test();
			\endverbatim
		*/
		template<class T>
		class Singleton
		{			
		public:
			//! Get the one and only instance
			/*!
				Returns the only instance of this Singleton class. Function is thread safe.
				Always returns the same pointer.
			*/
			static T& Instance()
			{
				if(instance == NULL)
				{
					CR::Utility::AutoLock<CR::Utility::CriticalSection> autoSection(section);
					if(instance == NULL)
					{
						T *temp;
						temp = new T();
						//needs to be ported, not safe without this.
						//InterlockedExchangePointer(reinterpret_cast<void**>(&instance),
						//	temp);
						instance = temp;
						atexit(Destroy);
					}
				}
				return *instance;
			}					
		protected:
			Singleton(void)	{}
			virtual ~Singleton(void) {}	
			static T *instance;
			static CR::Utility::CriticalSection section;
			//will be called by crt when module is unloaded
			static void Destroy()
			{
				if(instance != NULL)
					delete instance;
			}
		private:
			//prevent copying since only one of these can exist.
			Singleton<T>(const Singleton<T>& arg);
			const Singleton<T>& operator=(const Singleton<T>& arg);
		};

		template<class T>
		T* Singleton<T>::instance = NULL;

		template<class T>
		CR::Utility::CriticalSection Singleton<T>::section;
	}
}