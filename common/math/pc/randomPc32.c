#include "../random.h"

#include <stdlib.h>
#include <Windows.h>

void initRandomGenerator() {
	LARGE_INTEGER _time;
	QueryPerformanceCounter(&_time);
	srand((int)_time.LowPart);
}