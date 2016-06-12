#ifndef ADC_UTILS_H
#define ADC_UTILS_H

/* return the CONFIGPORT value
 * @return int the configPort value
 */
int getConfigPort(void);

/* return the CONFIGSCAN value
 * @return int the configScan parameters
 */
int getConfigScan(void);

/* set the CONFIGPORT value
 * @param data the configPort parameters
 */
void setConfigPort(int data);

/* set the CONFIGSCAN value
 * @param data the configSacn parameters
 */
void setConfigPort(int data);

/**
* Get a value of the channel (A / D conversion)
* @param channel the channel index between 0 and 11
* @return the value in millivolt.
*/
int getANX (char channel);


/**
 * define the port to be ADC.
 * @param index the index value
 * @param state 1/0 enable or disable
 */
void setANXConfig(int index, int state);

#endif

