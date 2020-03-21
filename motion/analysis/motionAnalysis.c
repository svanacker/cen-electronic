#include "motionAnalysis.h"

#include "../../common/serial/serial.h"
#include "../../common/serial/serialUtils.h"

#define SAMPLE_COUNT 20

static Sample samples[SAMPLE_COUNT];

static int sampleIndex = 0;

void initSamples(void) {
    int i;
    for (i = 0; i < SAMPLE_COUNT; i++) {
        Sample* localSample = &samples[i];
        localSample->pidTime = 0;
        localSample->positionLeft = 0;
        localSample->positionRight = 0;
    }
}

void addSample(int pidTime, int left, int right) {
    Sample* localSample = &samples[sampleIndex];
    localSample->pidTime = pidTime;
    localSample->positionLeft = left;
    localSample->positionRight = right;
    sampleIndex++;
}

void printSamples(void) {
    int i;
    for (i = 0; i < SAMPLE_COUNT; i++) {
        Sample* localSample = &samples[i];
        sendDec(localSample->pidTime);
        sendDec(localSample->positionLeft);
        sendDec(localSample->positionRight);
    }
    println();
}
