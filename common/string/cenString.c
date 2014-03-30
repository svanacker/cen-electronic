#include <string.h>

#include "cenString.h"

bool stringEquals(char* s1, char* s2) {
	int comparison = strcmp(s1, s2);
	return (comparison == 0);
}
