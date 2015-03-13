#pragma once
#include "CriticalSection.h"

namespace CR
{
	namespace Utility
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
		class AutoCriticalSection
		{
		public:
			//! Create a new AutoCriticalSection.
			/*!
				Enters the supplied CriticalSection. Will Leave the CriticalSection automaticly
				when the AutoCriticalSection is deleted.
				@param section The CriticalSection to lock on. Imediatly Enters the section.
			*/
			AutoCriticalSection(CriticalSection &section) 
			{
				this->section = &section;
				this->section->Enter();
			}
			//! Delete the AutoCriticalSection, Unlocking the CriticalSection
			~AutoCriticalSection(void)
			{
				section->Leave();
			}
		private:
			CriticalSection *section;
		};
	}
}