#include <p30fxxxx.h>
#include <UART.h>

#include "../../common/delay/delay30F.h"

#include "../../device/drivers/zigbee.h"

#include "../../test/recveiverZigBeeTest.h"


_FOSC(CSW_FSCM_OFF & XT_PLL16);  //7Mhz3728 * 16  = 117,9648 MHz /4 = 29,4912 MIPS maxi pour ce pic
_FWDT(WDT_OFF);					
//Watchdog OFF
//_FBORPOR(PBOR_OFF & BORV_27 & PWRT_16 & MCLR_EN);
_FGS(CODE_PROT_OFF);			//Codeprotect OFF


int main(void) {
	receiverZigbeeTest();

	return (0);
}

