#include <string.h>

#include "cenString.h"

BOOL stringEquals(char* s1, char* s2) {
	BOOL result = strcmp(s1, s2);
	return result;
}
