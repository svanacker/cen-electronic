#include <stdlib.h>
#include <stdio.h>
#include <p30fxxxx.h>
#include <libpic30.h>

#include <uart.h>
#include <stdarg.h>
#include <string.h>

#include <math.h>

typedef struct {
    int field;
} TestStruct;

TestStruct* testStruct;

int main() {
    float value = sin(0);

    printf("test");
    if (testStruct == NULL) {
        value = cos(0);
    }
    
    return value;
}
