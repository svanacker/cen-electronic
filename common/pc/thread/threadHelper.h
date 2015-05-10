#ifndef THREAD_HELPER_H
#define THREAD_HELPER_H

#include <stdio.h>
#include <Windows.h>

/**
 * Create thread with Default Options
 * @param lpStartAddress CallBack Function pointer
 * @param lpParameter the parameter which will be passed when callback will be called (Ex: PipeHandle ...)
 * @param lpThreadId the id of the Thread
 * @return the Handle for the Thread
 */
HANDLE createStandardThread(
    _In_ LPTHREAD_START_ROUTINE lpStartAddress,
    _In_opt_ __drv_aliasesMem LPVOID lpParameter,
    _Out_opt_ LPDWORD lpThreadId);

#endif