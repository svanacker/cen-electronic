#include <windows.h>
#include <stdbool.h>

#include "../cenDelay.h"

static LARGE_INTEGER Frequency;

// WINDOWS NON PORTABLE FUNCTION

void delaymSec(unsigned int mSecond) {
    Sleep(mSecond);
}

void initPerformanceCounter(void) {
    QueryPerformanceFrequency(&Frequency);
}

LONGLONG getElapsedTimeInMicroSeconds(LARGE_INTEGER StartingTime) {
    LARGE_INTEGER EndingTime, ElapsedMicroseconds;
    QueryPerformanceCounter(&EndingTime);
    ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;

    ElapsedMicroseconds.QuadPart *= 1000000;
    ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;

    return ElapsedMicroseconds.QuadPart;
}

void delayUs(void) {
    initPerformanceCounter();
    LARGE_INTEGER StartingTime;

    QueryPerformanceCounter(&StartingTime);
    while (true) {
        LONGLONG ElapsedMicroseconds = getElapsedTimeInMicroSeconds(StartingTime);
        if (ElapsedMicroseconds >= 1) {
            break;
        }
    }
}

void delay10us(char value) {
    initPerformanceCounter();
    LARGE_INTEGER StartingTime;

    QueryPerformanceCounter(&StartingTime);
    while (true) {
        LONGLONG ElapsedMicroseconds = getElapsedTimeInMicroSeconds(StartingTime);
        if (ElapsedMicroseconds >= 10 * value) {
            break;
        }
    }
}

void delay100us(char value) {
    initPerformanceCounter();

    LARGE_INTEGER StartingTime;
    QueryPerformanceCounter(&StartingTime);

    while (true) {
        LONGLONG ElapsedMicroseconds = getElapsedTimeInMicroSeconds(StartingTime);
        if (ElapsedMicroseconds >= 100 * value) {
            break;
        }
    }
}
