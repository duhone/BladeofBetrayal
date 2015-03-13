#pragma once


namespace CR
{
	namespace Utility
	{
		//! A high resolution timer.
		/*!
			Uses high resolution performance counter to implement a timer. High precesion.
			All returned values are in seconds. You should only call Update once per frame.
			The LastFrameTime is always the amount of time between the last 2 calls to update.

			Generally use GetTotalTime and Reset to keep track of the amount of time of a single event.
			Use Update only when creating a frame rate type counter.
		*/
		class Timer
		{
		public:
			Timer(void);
			~Timer(void);
			//! Total time since timer was created or Reset was called
			/*!
				This will be set back to 0 every time Reset is called.
			*/
			inline double GetTotalTime() const {return totalTime;} 
			//! Time between last 2 calls to Update
			/*!
				Don't use Reset if using this call and Update. Reset will set this back
				to 0, and it won't change from that until after the next Update call.
			*/
			inline double GetLastFrameTime() const {return timeLastFrame;}
			//! Reset the total time back to 0.
			void Reset(void);
			void StartFrame();
			//! Next Frame. Update the LastFrameTime
			void Update(void);
		private:

			unsigned int starttime;
			unsigned int currenttime;

			
			double timerFreqInv;
			double totalTime;
			double timeLastFrame;
			//LARGE_INTEGER lastFrameQuery;
		};
	}
}
