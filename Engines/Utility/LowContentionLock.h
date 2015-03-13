#pragma once

namespace CR
{
	namespace Utility
	{
		//not implemented
		/*class LowContentionLock
		{
		public:

			LowContentionLock(void)
			{
				m_event = CreateEvent(NULL,FALSE,FALSE,NULL);
				m_state = FREE;
			}

			~LowContentionLock(void)
			{
				CloseHandle(m_event);
			}
			inline void Enter()
			{
				//EnterCriticalSection(&section);
			}
			inline void EnterRead()
			{
				//EnterCriticalSection(&section);
			}
			inline void Leave()
			{
				//LeaveCriticalSection(&section);
			}
		private:
			enum State
			{
				FREE,
				LOCKED,
				WAITING
			};
			State m_state;
			HANDLE m_event;
			int m_threadCount;
		};*/
	}
}
