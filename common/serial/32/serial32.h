#ifndef SERIAL_32_H
#define SERIAL_32_H

#include <peripheral/uart.h>

/**
 * Returns the UART_MODULE object identifier by serial Port Index.
 * @param serialPortIndex the index of the serial port (@see serial.h)
 * @result a C structure provide by Microchip to store information about a specific UART
 */
UART_MODULE getUartModule(unsigned char serialPortIndex);

#endif
