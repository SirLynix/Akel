// This file is a part of Akel
// CREATED : 13/07/2021
// UPDATED : 13/07/2021

#ifndef __AK_TIME__
#define __AK_TIME__

#include <Akpch.h>

struct __time
{
	uint8_t sec = 0;
	uint8_t min = 0;
	uint8_t hour = 0;
	uint8_t day = 0;
	uint8_t month = 0;
	uint32_t year = 0;
};

namespace Ak
{
	class Time
	{
		public:
			static __time& getCurrentTime();

		private:
			inline static std::tm* _now;
			inline static __time _time;
	};
}

#endif // __AK_TIME__

