#pragma once
#include "CriticalSection.h"

namespace Syntax
{
	namespace Utility
	{
		namespace Threading
		{
			//!Used to ensure a critical section is never left locked.
			/*!
				Use to ensure a critical section is never left in a locked state,
				even if an exception occurs. Avoids deadlocks. Requires a CriticalSection object.
				The section will automaticly be unlocked when the AutoCriticalSection goes out of scope.

				Example:
				
				\verbatim
				class MyClass
				{
					CriticalSection section;

					void Test()
					{
						...
						{
							//this will be lock, and then automaticly unlock at the end of the closes surrounding
							//scope.
							AutoCriticalSection autosection(section); 
							...
						}	//unlocks here
						...
					}

				}
				\endverbatim
			*/
			template<class LockPolicy>
			class AutoLock 
			{
			public:
				//! Create a new AutoCriticalSection.
				/*!
					Enters the supplied CriticalSection. Will Leave the CriticalSection automaticly
					when the AutoCriticalSection is deleted.
					@param section The CriticalSection to lock on. Imediatly Enters the section.
				*/
				AutoLock(LockPolicy &lock) 
				{
					this->lock = &lock;
					this->lock->Enter();
				}
				//! Delete the AutoCriticalSection, Unlocking the CriticalSection
				~AutoLock(void)
				{
					lock->Leave();
				}
			private:
				LockPolicy *lock;
			};
			
			template<class LockPolicy>
			class AutoReadLock 
			{
			public:
				//! Create a new AutoCriticalSection.
				/*!
					Enters the supplied CriticalSection. Will Leave the CriticalSection automaticly
					when the AutoCriticalSection is deleted.
					@param section The CriticalSection to lock on. Imediatly Enters the section.
				*/
				AutoReadLock(LockPolicy &lock) 
				{
					this->lock = &lock;
					this->lock->EnterRead();
				}
				//! Delete the AutoCriticalSection, Unlocking the CriticalSection
				~AutoReadLock(void)
				{
					lock->Leave();
				}
			private:
				LockPolicy *lock;
			};
		}
	}
}