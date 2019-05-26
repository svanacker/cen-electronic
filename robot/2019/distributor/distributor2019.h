#ifndef DISTRIBUTOR_2019_H
#define DISTRIBUTOR_2019_H

#include "../../../common/color/color.h"

#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"

#include "../../../common/pwm/servo/servoList.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../common/timer/delayTimer.h"

#include "../../../drivers/tof/tofList.h"

/**
 * Prepare the fork to take something on the Distributor
 * @param servoList
 * @param leftRight
 * @return 
 */
bool distributor2019PrepareTake(ServoList* servoList);

/**
 * All actions to take a 2 Pucks.
 * @param servoList
 */
bool distributor2019Take(ServoList* servoList, TofSensorList* tofSensorList);


#endif
