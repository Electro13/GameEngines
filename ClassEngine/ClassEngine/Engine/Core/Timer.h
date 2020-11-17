#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

class Timer{
public:
	Timer(const Timer&) = delete;
	Timer(Timer&&) = delete;
	Timer& operator=(const Timer&) = delete;
	Timer& operator=(Timer&&) = delete;
	
	Timer();
	void Start(); // Starts the timer
	void UpdateFrameTicks(); // Updates frame ticks
	float GetDeltaTime() const; // Gets the delta time
	unsigned int GetSleepTime(const unsigned int fps_); // This gets how much time the engine should sleep for
	float GetCurrentTicks() const; // Gets the current tick
private:
	unsigned int prevTicks, currentTicks; // these have to be unsigned because time can't be negative
};
#endif
