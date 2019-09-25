#ifndef LCD_HD44780_H
#define LCD_HD44780_H

#include <stdbool.h>

/*******************
* Definition des ports utilisés pour utiliser l'afficheur LCD
********************/


#ifdef PROG_32
    #define RW_LCD  PORTFbits.RF3
    #define RS_LCD  PORTFbits.RF1
    #define E_LCD   PORTFbits.RF0

    #define D0_LCD  PORTEbits.RE0
    #define D1_LCD  PORTEbits.RE1
    #define D2_LCD  PORTEbits.RE2
    #define D3_LCD  PORTEbits.RE3
    #define D4_LCD  PORTEbits.RE4
    #define D5_LCD  PORTEbits.RE5
    #define D6_LCD  PORTEbits.RE6
    #define D7_LCD  PORTEbits.RE7
    #define D11_LCD PORTDbits.RD11

    #define TRIS_RS_LCD TRISFbits.TRISF1
    #define TRIS_RW_LCD TRISFbits.TRISF3
    #define TRIS_E_LCD  TRISFbits.TRISF0

    #define TRIS_D11_LCD TRISDbits.TRISD11

    #define TRIS_D0_LCD TRISEbits.TRISE0
    #define TRIS_D1_LCD TRISEbits.TRISE1
    #define TRIS_D2_LCD TRISEbits.TRISE2
    #define TRIS_D3_LCD TRISEbits.TRISE3
    #define TRIS_D4_LCD TRISEbits.TRISE4
    #define TRIS_D5_LCD TRISEbits.TRISE5
    #define TRIS_D6_LCD TRISEbits.TRISE6
    #define TRIS_D7_LCD TRISEbits.TRISE7


#else

    #define RS_LCD             LATBbits.LATB4
    #define RW_LCD             LATBbits.LATB5
    #define E_LCD              LATBbits.LATB8
    
    #define D4_LCD             LATBbits.LATB9
    #define D5_LCD             LATBbits.LATB10
    #define D6_LCD             LATBbits.LATB11
    #define D7_LCD             LATBbits.LATB12
    
    #define TRIS_RS_LCD         TRISBbits.TRISB4
    #define TRIS_RW_LCD     TRISBbits.TRISB5
    #define TRIS_E_LCD         TRISBbits.TRISB8
    
    #define TRIS_D4_LCD     TRISBbits.TRISB9
    #define TRIS_D5_LCD     TRISBbits.TRISB10
    #define TRIS_D6_LCD     TRISBbits.TRISB11
    #define TRIS_D7_LCD        TRISBbits.TRISB12
 #endif
    
/**
* Initialise l'afficheur LCD
* 
*/
void hd44780_initLcd (void);

/**
* Envoie une commande à l'afficheur sur 8bits
*/
void hd44780_sendComLcd (unsigned char value);


/**
* Envoie une commande à l'afficheur lors de l'initialisation sur 4bits
*/
void hd44780_sendIniComLcd (unsigned char D7, unsigned char D6, unsigned char D5, unsigned char D4);

/**
* Envoie une data à l'afficheur
*/
void hd44780_sendDataLcd (unsigned char DataLcd );

/**
* Show a string
* @param text to send
*/
void hd44780_writeString ( const char *text );

/**
* Affiche une chaine de texte
* @param texte à transmettre
* @param colonne
* @param ligne
*/
void hd44780_affTexteLcdXY( const char *text, unsigned char colonneLcd, unsigned char ligneLcd );

/**
* Set the cursor at the specified row and column.
* @param row row index between 1 and 4 = N° de la ligne de 1 à 4
* @param column column index de 1 à 20
*/
void hd44780_setCursorRowAndColumn(unsigned char row, unsigned char column);

/**
* Hide the cursor.
*/
void hd44780_hideCursor (void);

/**
* Set an underline to see the cursor.
*/
void hd44780_showUnderlineCursor (void);

/**
 * Set or not the backlight.
 */
void hd44780_setBacklight(bool enabled);

/**
* Use blink cursor.
*/
void hd44780_setBlinkCursor(void);

/**
* Set the cursor at the top and left of the screen.
*/
void hd44780_setCursorAtHome(void);

/**
* Efface l'écran
*/
void hd44780_clearScreen ( void );

/**
* Affiche un caractere à la position actuel du curseur et décal de 1 le curseur
* @param Caractère à afficher
*/
void hd44780_writeChar ( unsigned char carac );

#endif
