#include "transmitMode.h"

const char* getTransmitModeAsString(TransmitMode transmitMode) {
    switch (transmitMode) {
        case TRANSMIT_LOCAL : return "TRANSMIT_LOCAL";
        case TRANSMIT_UART : return "TRANSMIT_UART";
        case TRANSMIT_I2C : return "TRANSMIT_I2C";
        case TRANSMIT_ZIGBEE : return "TRANSMIT_ZIGBEE";
        default : return "TRANSMIT_???";
    }
}