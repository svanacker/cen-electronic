/**
* Device to handle the battery voltage.
*/
#include <p30Fxxxx.h>
#include <libpic30.h>

#include "battery.h"

#include "../../common/adc/adcutils.h"

// COMMON PART

/**
* Init the device
*/
void initBattery() {

}

/**
 * Returns the revision of the Software.
 */
unsigned int getBatterySoftwareRevision() {
    return 1;
}

const char* getBatteryDeviceName() {
    return "Battery";
}

unsigned int isBatteryDeviceOk() {
  // we consider that the voltage must be over 12 V
  return getBatteryVoltage(0) > 12000;
}

int getBatteryVoltage(int batteryIndex) {
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

/*
int getMaskBatteryLevel(int batteryIndex) {
  int value = getBatteryVoltage(batteryIndex);
  if (value > 17000) {
    return 0b0111;
  }
  if (value > 16000) {
    return 0b0011;
  }
  if (value > 15000) {
    return 0b0001;
  }
  return 0b0000;
}
*/

/**
* Shows the level of the battery.
*/
/*
void showBatteryLevel(int batteryIndex) {
  int value = getMaskBatteryLevel(batteryIndex);
  PORTBbits.RB10 = value && 0b0001;
  PORTBbits.RB11 = value && 0b0010;
  PORTBbits.RB12 = value && 0b0100;
}
*/

// DEVICE INTERFACE

void stopBattery() {

}

DeviceDescriptor getBatteryDeviceDescriptor() {
    DeviceDescriptor result;
    result.deviceInit = &initBattery;
    result.deviceShutDown = &stopBattery;
    result.deviceIsOk = &isBatteryDeviceOk;
    result.deviceGetSoftwareRevision = &getBatterySoftwareRevision;
    result.deviceGetName = &getBatteryDeviceName;
    result.enabled = 1;

    return result;
}
