#include "startMatchDetector.h"

void initStartMatchDetector(StartMatchDetector* startMatchDetector, IsMatchStartedFunction* isMatchStartedFunctionParam) {
    startMatchDetector->isMatchStartedFunction = isMatchStartedFunctionParam;
}
