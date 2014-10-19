#ifndef SERIAL_32_H
#define SERIAL_32_H

//#include <uart.h>
#include <peripheral/uart.h>

/**
 * Returns the UART_MODULE object identifier by serial Port Index.
 */
UART_MODULE getUartModule(unsigned char serialPortIndex);

#endif
