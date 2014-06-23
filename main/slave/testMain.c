#include <p30Fxxxx.h>

#include "../../device/deviceDataDispatcher.h"

#include "../../device/device.h"
#include "../../device/drivers/deviceTest.h"
#include "../../device/drivers/driverTest.h"

_FOSC(CSW_FSCM_OFF & XT_PLL16);  //7Mhz3728 * 16  = 117,9648 MHz /4 = 29,4912 MIPS maxi pour ce pic
_FWDT(WDT_OFF);                    //Watchdog OFF
//_FBORPOR(PBOR_OFF & BORV_27 & PWRT_16 & MCLR_EN);
_FGS(CODE_PROT_OFF);            //Codeprotect OFF



int main (void) {
    // Initialisation du périphérique
    const DeviceDescriptor *deviceTestDescriptor = getTestDeviceDescriptor();
    initDevice(deviceTestDescriptor, false);

    // Initialisation du répartiteur de données
    const DeviceDescriptor *devices[] = {deviceTestDescriptor};
    deviceDataDispatcherSetDevices(devices);

    // Initialisation du pilote
    const DriverDescriptor *driverTestDescriptor = driverTestGetDescriptor();
    driverInit(driverTestDescriptor, false);

    int value = 0;
    int key = 0;

    // appel direct au device
    value = deviceTestGetValue(key);
    // on vérifie que value = key + 1

    // réinitialisation de value
    value = 0;

    // appel indirect au device via le driver et le dispatcher
    value = driverTestGetValue(key);
    // on vérifie que value = key + 1

    while (1);
}    
