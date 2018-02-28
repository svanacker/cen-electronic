#include "pidMotionError.h"

void clearMotionError(PidMotionError* pidMotionError) {
    pidMotionError->previousError = 0;
    pidMotionError->error = 0;
    pidMotionError->derivativeError = 0;
    pidMotionError->integralError = 0;
}

void printErrorStruct (OutputStream* outputStream, int index ) {
    // TODO 
    /*
    MotionError* localErr = getMotionError(index);

    appendStringAndDecf(outputStream, "pe=", localErr->previousError);
    appendStringAndDecf(outputStream, ",e=", localErr->error);
    appendStringAndDecf(outputStream, ",de=", localErr->derivativeError);
    appendStringAndDecf(outputStream, "ie=", localErr->integralError);
    println(outputStream);
    */
}