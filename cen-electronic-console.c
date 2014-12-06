#include <stdio.h>
#include <stdlib.h>

#include <windows.h>
#include <process.h>

#include "test/main/mainBoard32/mainBoard32Pc.h"
#include "test/allTests.h"

unsigned __stdcall test(void* pArguments) {
	printf("test");

	_endthreadex(0);

	return 0;
}

int main(int argc, char *argv[])
{
	// runAllTests();
	
	runMainBoard32PC();

	/*
	HANDLE hThread;
	unsigned threadID;
	hThread = (HANDLE)_beginthreadex(NULL, 0, &test, NULL, 0, &threadID);
	printf("main");
	*/
	
	getchar();
	return EXIT_SUCCESS;
}


