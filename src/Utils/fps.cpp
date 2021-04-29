// This file is a part of AtlasEngine
// CREATED : 29/04/2021
// UPDATED : 29/04/2021

#include <Utils/utils.h>

namespace AE
{
	CounterFPS::CounterFPS()
	{}

	void CounterFPS::start()
	{
		timer = SDL_GetTicks();
		before = static_cast<long long>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
		now = static_cast<long long>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());		
	}
	
	void CounterFPS::update()
	{
		now = static_cast<long long>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());

        if(SDL_GetTicks() - timer > 1000)
        {
            outputFPS = fps;
			outputTicks = ticks;
			ticks = 0;
            fps = 0;
            timer += 1000;
        }

		fps++;

		elapsed_time = now - before;
		if(elapsed_time >= ns)
        {
            ticks++;
            before += ns;
		}
	}

	int CounterFPS::getFPS()
	{
		return outputFPS;
	}

	int CounterFPS::getTicks()
	{
		return outputTicks;
	}

	CounterFPS::~CounterFPS()
	{}
}

