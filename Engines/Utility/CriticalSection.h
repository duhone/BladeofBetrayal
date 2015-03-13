#pragma once

namespace CR
{
	namespace Utility
	{
		//!Critical section wrapper class. Use for thread syncronization
		/*!
			Simple wrapper class. Be sure to call leave every time you call enter. If
			you don't you can cause a deadlock in your application. Watch out for Exceptions.
			Use AutoCriticalSection to avoid these problems.

			Example:
			\verbatim
			class MyClass
			{
				CriticalSection section;

				void Test()
				{
					section.Enter(); //Only one thread at a time allowed past this call

					section.Leave();
				}

			}
			\endverbatim
		*/
		class CriticalSection
		{
		public:
			//! create a new critical section. Initializes internal win32 section.
			CriticalSection(void)
			{
				//InitializeCriticalSection(&section);
			}
			//! Deletes the internal win32 section.
			~CriticalSection(void)
			{
				//DeleteCriticalSection(&section);
			}
			//!Enter the critical section.
			/*!
				Only one thread allowed to enter at a time. This function will cause any other threads to freeze
				here until the first threads leaves the section. Be sure to leave once for every enter, or you
				can cause a deadlock.
			*/
			inline void Enter()
			{
				//EnterCriticalSection(&section);
			}
			inline void EnterRead()
			{
				//EnterCriticalSection(&section);
			}
			//!Leave the critical section.
			/*!
				Leave the critical section. Only valid if enter has been called.
			*/
			inline void Leave()
			{
				//LeaveCriticalSection(&section);
			}
		private:
			//CRITICAL_SECTION section;
		};
	}
}
