#ifndef COMMON_TIMER_H
#define COMMON_TIMER_H

#include <time.h>

namespace Ouroboros { namespace Common
{

	// Timer class is used for profiling
	class Timer
	{
	public:
		Timer();

		void Init();
		double GetTime();

	private:
		clock_t startTime;
		clock_t endTime;
	};

}}

#endif // COMMON_TIMER_H