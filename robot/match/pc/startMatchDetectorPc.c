#include "startMatchDetectorPc.h"
#include "../startMatchDetector.h"

#include <stdbool.h>

static bool matchStarted;

void startMatchPc(void) {
	matchStarted = true;
}

bool isMatchStartedPc(StartMatchDetector* startMatchDetector) {
	return matchStarted;
}

void initStartMatchDetectorPc(StartMatchDetector* startMatchDetector) {
	initStartMatchDetector(startMatchDetector, isMatchStartedPc);
}
