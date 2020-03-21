#ifndef START_MATCH_DETECTOR_PC_H
#define START_MATCH_DETECTOR_PC_H

#include "../startMatch.h"


#define START_MATCH_DETECTOR_PC_FILE_NAME              "startMatchDetectorPc.txt"

#define START_MATCH_DETECTOR_PC_FILE_LENGTH                                    1

/**
 * To be able to simulate the start of the match when using a pc.
 */
void startMatchPc(void);

/**
 * To detect on a file if the match is started or not.
 */
bool isMatchStartedPc(StartMatch* startMatch);

#endif
