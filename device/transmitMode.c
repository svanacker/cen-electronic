#include "transmitMode.h"

const char* getTransmitModeAsString(const TransmitMode transmitMode) {
    switch (transmitMode) {
        case TRANSMIT_LOCAL: return "LOCAL";
        case TRANSMIT_UART: return "UART";
        case TRANSMIT_I2C: return "I2C";
        case TRANSMIT_ZIGBEE: return "ZIGBEE";
        default: return "TRANSMIT_???";
    }
}
