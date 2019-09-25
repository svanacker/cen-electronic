#include <p30Fxxxx.h>

#include "pliersDevice2011.h"

#include "pliersDeviceInterface2011.h"

#include "../../common/commons.h"

#include "../../common/cmd/commonCommand.h"

#include "../../common/delay/cenDelay.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/pwm/servo/servoPwm.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../main/meca1/mechanicalBoard1.h"

void devicePliers2011Init() {
    stopPlier(1);
    stopPlier(2);
}

void devicePliers2011ShutDown() {
    stopPlier(1);
    stopPlier(2);
}

bool devicePliers2011IsOk() {
    return true;
}

void movePlier(int index, int value) {
    int i = 0;
    for (i = 0; i < 2; i++) {
        pwmServoAll(20000, 20000);
        pwmServo(index, 20000, value);
        delaymSec(50);
    }
}

void stopPlier(int index) {
    movePlier(index, PWM_SERVO_MIDDLE_POSITION);
}

#define PLIERS_CLOSE_PWM         1150
#define PLIERS_CLOSE_END_PWM         1300

#define PLIERS_INIT_CLOSE_PWM         1400

#define PLIERS_OPEN_PWM         2000

// Valeur plus faible pour arriver en douceur
#define PLIERS_END_OPEN_PWM         1650

void movePliers(int delayCounter, int speed) {
    int counter = 0;
    while (1) {
        counter++;
        if (counter > delayCounter) {
            break;
        }
        movePlier(1, speed);
        movePlier(2, speed);
    }

    stopPlier(1);
    stopPlier(2);
}

void openPliers(int delayCounter, int speed) {
    bool rightOpened = false;
    bool leftOpened = false;
    int counter = 0;
    while (1) {
        counter++;
        // 2 seconds
        if (counter > delayCounter) {
            break;
        }

        if (!rightOpened && PIN_SWITCH_PLIER_OPEN_RIGHT) {
            appendString(getInfoOutputStreamLogger(), "Pliers Right Opened\n");
            rightOpened = true;
            stopPlier(1);
        } else if (!rightOpened) {
            movePlier(1, speed);
        }

        if (!leftOpened && PIN_SWITCH_PLIER_OPEN_LEFT) {
            appendString(getInfoOutputStreamLogger(), "Pliers Left Opened\n");
            leftOpened = true;
            stopPlier(2);
        } else if (!leftOpened) {
            movePlier(2, speed);
        }
        if (rightOpened && leftOpened) {
            break;
        }
    }
    appendString(getInfoOutputStreamLogger(), "Both Pliers Opened\n");

    stopPlier(1);
    stopPlier(2);
}

/*
void closePliers(int delayCounter, int speed) {
        movePliers(delayCounter, speed);
}
 */

void closePliers(int delayCounter, int speed) {
    bool rightClosed = false;
    bool leftClosed = false;
    int counter = 0;
    while (1) {
        counter++;
        // 2 seconds
        if (counter > delayCounter) {
            break;
        }

        if (!rightClosed && PIN_SWITCH_PLIER_CLOSE_RIGHT) {
            appendString(getInfoOutputStreamLogger(), "Pliers Right Closed\n");
            rightClosed = true;
            stopPlier(1);
        } else if (!rightClosed) {
            movePlier(1, speed);
        }

        if (!leftClosed && PIN_SWITCH_PLIER_CLOSE_LEFT) {
            appendString(getInfoOutputStreamLogger(), "Pliers Left Closed\n");
            leftClosed = true;
            stopPlier(2);
        } else if (!leftClosed) {
            movePlier(2, speed);
        }
        if (rightClosed && leftClosed) {
            break;
        }
    }
    appendString(getInfoOutputStreamLogger(), "Both Pliers Closed\n");

    stopPlier(1);
    stopPlier(2);
}

void devicePliers2011HandleRawData(char header,
        InputStream* inputStream,
        OutputStream* outputStream) {
    if (header == COMMAND_PLIERS_2011_INIT_CLOSE) {
        appendAck(outputStream);
        append(outputStream, COMMAND_PLIERS_2011_INIT_CLOSE);

        // D�marre p�chu
        closePliers(2, PLIERS_CLOSE_PWM);

        // Fini en douceur
        closePliers(5, PLIERS_INIT_CLOSE_PWM);

        appendString(getInfoOutputStreamLogger(), "Init Pliers End\n");
    } else if (header == COMMAND_PLIERS_2011_CLOSE) {
        appendAck(outputStream);
        append(outputStream, COMMAND_PLIERS_2011_CLOSE);

        // D�marre p�chu
        closePliers(2, PLIERS_CLOSE_PWM);

        // Fermeture moins forte
        closePliers(4, PLIERS_CLOSE_END_PWM);
        appendString(getInfoOutputStreamLogger(), "Close Pliers End\n");
    } else if (header == COMMAND_PLIERS_2011_OPEN) {
        appendAck(outputStream);
        append(outputStream, COMMAND_PLIERS_2011_OPEN);

        // Pour arracher si la pince est un peu bloqu�e
        if (!PIN_SWITCH_PLIER_OPEN_RIGHT || !PIN_SWITCH_PLIER_OPEN_LEFT) {
            movePliers(2, PLIERS_OPEN_PWM);
        }

        // Pour arriver en douceur
        openPliers(8, PLIERS_END_OPEN_PWM);
    }
}


static DeviceDescriptor descriptor = {
    .deviceInit = &devicePliers2011Init,
    .deviceShutDown = &devicePliers2011ShutDown,
    .deviceIsOk = &devicePliers2011IsOk,
    .deviceHandleRawData = &devicePliers2011HandleRawData,
};

DeviceDescriptor* getPliers2011DeviceDescriptor() {
    return &descriptor;
}
