/**
* Device to handle the battery voltage.
*/

#include "battery.h"

#include <stdlib.h>
#include <stdbool.h>

#include "../../common/adc/adcutils.h"

// COMMON PART

unsigned int getBatteryVoltage(Battery* battery) {
  int value = (long) getANX(BATTERY_ADC_INDEX);
  // AN conversion of PIC : 12 bits
  // 0V -> 0
  // 5V -> 2^12 = 4096

  // The voltage bridge divisor is 1/4. We use a voltage bridge divisor
  // because we want to measure values between 0 and 20 V, but the PIC only
  // supports input between 0 and 5V
  // BatteryVoltage = 0V => 0V
  // BatteryVoltage = 20V => 5V as input for the Pin
  // BatteryValue = PinVoltage * 4
  // PinVoltage = (PinValue / 4096) * 5 (5V)
  // (4 * 5) / 4096L => 1/ 204.8 (factor)
  // we multiply by 1000 to have the value => 1/200 * 1000 = 5
  int result = (value * 5);
  return result;
}

bool isBatteryInitialized(Battery* battery) {
    if (battery == NULL) {
        return false;
    }
    if (battery->readBatteryValue == NULL) {
        return false;
    }
    return true;
}

void initBattery(Battery* battery, ReadBatteryVoltageFunction* readBatteryValue) {
    if (battery == NULL) {
        return;
    }
    battery->readBatteryValue = readBatteryValue;
}