#pragma once
#include "CriticalSection.h"
#include "AutoLock.h"

namespace Syntax
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
					Syntax::Utility::Threading::AutoLock<Syntax::Utility::Threading::CriticalSection> autoSection(section);
					if(instance == NULL)
					{
						T *temp;
						temp = new T();
						InterlockedExchangePointer(reinterpret_cast<void**>(&instance),
							temp);
						atexit(Destroy);
					}
				}
				return *instance;
			}
		protected:
			static T *instance;
			static Syntax::Utility::Threading::CriticalSection section;
			Singleton(void)	{}
			virtual ~Singleton(void) {}
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
		Syntax::Utility::Threading::CriticalSection Singleton<T>::section;
	}
}