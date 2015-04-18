#include "pidParameter.h"
#include "../pid.h"

#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"

void printPidParameter(OutputStream* outputStream, int pidIndex) {
    unsigned char rollingTestMode = getRollingTestMode();
    PidParameter* localPidParameter= getPidParameter(pidIndex, rollingTestMode);

    appendStringAndDecf(outputStream, "p=", localPidParameter->p);
    appendStringAndDecf(outputStream, ",i=", localPidParameter->i);
    appendStringAndDecf(outputStream, ",d=", localPidParameter->d);
    appendStringAndDecf(outputStream, ",mi=", localPidParameter->maxIntegral);

    println(outputStream);
}

void printAllPidParameters(OutputStream* outputStream) {
    int i;
    int pidCount = PID_COUNT;
    for (i = 0; i < pidCount; i++) {
        appendDec(outputStream, i);
        append(outputStream, ':');
        printPidParameter(outputStream, i);
    }
}
