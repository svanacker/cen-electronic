#include <math.h>

#include "gp2y0a21yk.h"

float gp2y0a21ykGetCentimerDistanceForTension(float milliVolt) {
    int valueToCompare = milliVolt;
    if (valueToCompare > 0x300) {
        // Must not detect something at this range
        return 300;
    } else if (valueToCompare > 0x200) {
        return 10;
    } else if (valueToCompare > 0x190) {
        return 15;
    } else if (valueToCompare > 0x180) {
        return 20;
    } else if (valueToCompare > 0x167) {
        return 30;
    } else if (valueToCompare > 0x140) {
        return 40;
    }// Value to confirm !!
    else if (valueToCompare > 0x100) {
        return 50;
    } else if (valueToCompare > 0x090) {
        return 60;
    } else if (valueToCompare > 0x080) {
        return 70;
    } else if (valueToCompare > 0x070) {
        return 80;
    }
    // Not detected
    return 300;
}
