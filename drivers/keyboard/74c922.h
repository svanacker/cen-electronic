/* 
 * File:   74c922.h
 * Author: f4deb
 *
 * Created on 28 septembre 2014, 21:10
 */

#ifndef C922_H
#define	C922_H

#define KDF PORTGbits.RG2
#define KDE PORTGbits.RG3
#define KEYBOARD_DATA_AVAILABLE PORTGbits.RG6
#define KEYBOARD_OUTPUT_ENABLE  PORTGbits.RG9
#define KDA PORTDbits.RD5
#define KDB PORTDbits.RD6
#define KDC PORTDbits.RD7
#define KDD PORTDbits.RD8

/**
 * Initialize the port for 74C922.
 **/
void init74c922 (void);


/**
 * Read the keybord
 * @return char     charactere code
 *         0xff for no caractere
 **/
char readKey (void);


#endif	/* 74C922_H */