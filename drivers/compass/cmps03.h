/**********************************
* recupere la version dans le pic de la carte CMPS03
* @return : version du pic
**********************************/
char getRevCMPS03 (void);

/**********************************
* recupere le cap 
* @return : cap, 0-255 pour 360 degrés
**********************************/
char getByteCMPS03(void);

/**********************************
* recupere le cap 
* @return : cap, 0-3599 pour 0-359.9deg
**********************************/
unsigned int getDegCMPS03(void);
