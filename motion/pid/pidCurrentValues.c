#include "pidCurrentValues.h"

void clearPidCurrentValues(PidCurrentValues* pidCurrentValues) {
    pidCurrentValues->position = 0;
    pidCurrentValues->oldPosition = 0;
    pidCurrentValues->u = 0;
}