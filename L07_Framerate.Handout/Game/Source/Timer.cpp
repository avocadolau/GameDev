// ----------------------------------------------------
// Fast timer with milisecons precision
// ----------------------------------------------------

#include "Timer.h"
#include "SDL\include\SDL_timer.h"

// L07: TODO 1: Fill Start(), Read(), ReadSec() methods
// they are simple, one line each!
	
Timer::Timer()
{
	Start();
}

void Timer::Start()
{
	startTime = SDL_GetTicks();
}

uint32 Timer::Read() const
{
	uint32 ret = SDL_GetTicks() - startTime;
	return ret;
}

float Timer::ReadSec() const
{
	return (float)(SDL_GetTicks() - startTime) / 1000.0f;
}