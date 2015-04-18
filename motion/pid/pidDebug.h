#ifndef PID_DEBUG_H
#define PID_DEBUG_H

#include "pid.h"
#include "motionInstruction.h"

#include "../../common/commons.h"
#include "../../common/io/outputStream.h"


void printPid(OutputStream* outputStream, int pidIndex);

void printAllPids(OutputStream* outputStream);

#endif
