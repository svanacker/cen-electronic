#include "threadHelper.h"

#include <conio.h>
#include <Windows.h>

HANDLE createStandardThread(
        _In_ LPTHREAD_START_ROUTINE lpStartAddress,
        _In_opt_ __drv_aliasesMem LPVOID lpParameter,
        _Out_opt_ LPDWORD lpThreadId) {

    HANDLE result;
    // Create a thread to handle master to slave data
    result = CreateThread(
            NULL, // no security attribute 
            (SIZE_T) 0, // default stack size 
            lpStartAddress, // thread proc
            lpParameter, // thread parameter 
            0, // not suspended 
            lpThreadId); // returns thread ID 


    if (result == NULL) {
        printf("CreateThread failed, lastError=%d.\n", GetLastError());
    }

    return result;
}
