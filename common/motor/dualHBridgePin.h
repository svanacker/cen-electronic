#ifndef DUAL_H_BRIDGE_PIN
#define DUAL_H_BRIDGE_PIN

#include <stdbool.h>

/**
 * Define the type of action to do when analyzing stop event.
 */
enum DualHBridgePinUsageType {
    /** The pin is not assigned */
    PIN_USAGE_TYPE_NO_USAGE = 0,
    /** The pin is assigned to detect end when going forward of the motor 1 */
    PIN_USAGE_TYPE_MOTOR_1_FORWARD_END = 1,
    /** The pin is assigned to detect end when going backward of the motor 1*/
    PIN_USAGE_TYPE_MOTOR_1_BACKWARD_END = 2,
    /** The pin is assigned to detect start when going forward of the motor 2 */
    PIN_USAGE_TYPE_MOTOR_2_FORWARD_END = 3,
    /** The pin is assigned to detect end when going backward of the motor 2 */
    PIN_USAGE_TYPE_MOTOR_2_BACKWARD_END = 4
};

/**
 * Define the type of action to do when analyzing stop event.
 */
enum DualHBridgePinStopEventType {
    /** No Action to do */
    PIN_STOP_EVENT_NO_ACTION = 0,
    /** If we must stop when the value is low. */
    PIN_STOP_EVENT_LOW_STOP = 1,
    /** If we must stop when the value is high. */
    PIN_STOP_EVENT_HIGH_STOP = 2,
};

#endif
