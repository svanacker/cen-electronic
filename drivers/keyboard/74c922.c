#include <p32xxxx.h>
#include "74c922.h"


void init74c922 (void){
    //Initialisation des ports du PIC pour le control du 74c922

    TRISGbits.TRISG2 = 1; // KDF
    TRISGbits.TRISG3 = 1; // KDE
    TRISGbits.TRISG6 = 1; // KEYBOARD_DATA_AVAILABLE
    TRISGbits.TRISG9 = 0; // KEYBOARD_OUTPUT_ENABLE
    TRISDbits.TRISD5 = 1; // KDA
    TRISDbits.TRISD6 = 1; // KDB
    TRISDbits.TRISD7 = 1; // KDC
    TRISDbits.TRISD8 = 1; // KDD
}

char readKey (void){
    char data = 0xFF;

    // TEST si une touche est active
    if ( KEYBOARD_DATA_AVAILABLE == 1 ){
        // Active la lecture de l'encodeur
        KEYBOARD_OUTPUT_ENABLE = 1;

        data = PORTD>>5 ;

        // Desactive la lecture de l'encodeur
        KEYBOARD_OUTPUT_ENABLE = 0;
        data = data & 0b00001111;

    }

    return (data );
}
