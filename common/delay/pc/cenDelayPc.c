#include <windows.h>
#include <stdbool.h>

#include "../cenDelay.h"

static LARGE_INTEGER Frequency;

// WINDOWS NON PORTABLE FUNCTION

void delayMilliSecs(unsigned int mSecond) {
    Sleep(mSecond);
}

void initPerformanceCounter(void) {
    if (Frequency.QuadPart == 0) {
        QueryPerformanceFrequency(&Frequency);
    }
}

LONGLONG getElapsedTimeInMicroSeconds(LARGE_INTEGER StartingTime) {
    initPerformanceCounter();
    LARGE_INTEGER EndingTime, ElapsedMicroseconds;
    QueryPerformanceCounter(&EndingTime);
    ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;

    ElapsedMicroseconds.QuadPart *= 1000000;
    ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;

    return ElapsedMicroseconds.QuadPart;
}

void delayMicroSecs(unsigned int microSeconds) {
    initPerformanceCounter();
    LARGE_INTEGER StartingTime;

    QueryPerformanceCounter(&StartingTime);
    while (true) {
        LONGLONG ElapsedMicroseconds = getElapsedTimeInMicroSeconds(StartingTime);
        if (ElapsedMicroseconds >= microSeconds) {
            break;
        }
    }
}
