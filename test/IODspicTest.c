#include <p30fxxxx.h>

#include "../common/delay/delay30F.h"

void testPortA (void){
    TRISAbits.TRISA11 = 0;

    delaymSec(1);
    LATAbits.LATA11= 0;

    delaymSec(1);
    LATAbits.LATA11 = 1;
}

void testPortB (void){

    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;
    TRISBbits.TRISB2 = 0;
    TRISBbits.TRISB3 = 0;
    TRISBbits.TRISB4 = 0;
    TRISBbits.TRISB5 = 0;
    TRISBbits.TRISB6 = 0;
    TRISBbits.TRISB7 = 0;
    TRISBbits.TRISB8 = 0;
    TRISBbits.TRISB9 = 0;
    TRISBbits.TRISB10 = 0;
    TRISBbits.TRISB11 = 0;
    TRISBbits.TRISB12 = 0;

    LATBbits.LATB0=0;
    LATBbits.LATB1=0;
    LATBbits.LATB2=0;
    LATBbits.LATB3=0;
    LATBbits.LATB4=0;
    LATBbits.LATB5=0;
    LATBbits.LATB6=0;
    LATBbits.LATB7=0;
    LATBbits.LATB8=0;
    LATBbits.LATB9=0;
    LATBbits.LATB10=0;
    LATBbits.LATB11=0;
    LATBbits.LATB12=0;
    delaymSec(1);
    LATBbits.LATB0=1;
    LATBbits.LATB1=1;
    LATBbits.LATB2=1;
    LATBbits.LATB3=1;
    LATBbits.LATB4=1;
    LATBbits.LATB5=1;
    LATBbits.LATB6=1;
    LATBbits.LATB7=1;
    LATBbits.LATB8=1;
    LATBbits.LATB9=1;
    LATBbits.LATB10=1;
    LATBbits.LATB11=1;
    LATBbits.LATB12=1;
    delaymSec(1);
}

void testPortC (void){

//PORTC15 only whithout quartz

    TRISCbits.TRISC13 = 0;
    TRISCbits.TRISC14 = 0;
//    TRISCbits.TRISC15 = 0;

    LATCbits.LATC13=0;
    LATCbits.LATC14=0;
//    LATCbits.LATC15=0;
    delaymSec(1);

    LATCbits.LATC13=1;
    LATCbits.LATC14=1;
//    LATCbits.LATC15=1;
    delaymSec(1);
}

void testPortD (void){

    TRISDbits.TRISD0 = 0;
    TRISDbits.TRISD1 = 0;
    TRISDbits.TRISD2 = 0;
    TRISDbits.TRISD3 = 0;
    TRISDbits.TRISD8 = 0;
    TRISDbits.TRISD9 = 0;


    LATDbits.LATD0=0;
    LATDbits.LATD1=0;
    LATDbits.LATD2=0;
    LATDbits.LATD3=0;
    LATDbits.LATD8=0;
    LATDbits.LATD9=0;
    delaymSec(1);

    LATDbits.LATD0=1;
    LATDbits.LATD1=1;
    LATDbits.LATD2=1;
    LATDbits.LATD3=1;
    LATDbits.LATD8=1;
    LATDbits.LATD9=1;
    delaymSec(1);
}

void testPortF (void){



    TRISFbits.TRISF0 = 0;
    TRISFbits.TRISF1 = 0;
    TRISFbits.TRISF2 = 0;
    TRISFbits.TRISF3 = 0;
    TRISFbits.TRISF5 = 0;
    TRISFbits.TRISF4 = 0;
    TRISFbits.TRISF6 = 0;


    LATFbits.LATF0=0;
    LATFbits.LATF1=0;
    LATFbits.LATF2=0;
    LATFbits.LATF3=0;
    LATFbits.LATF5=0;
    LATFbits.LATF4=0;
    LATFbits.LATF6=0;
    delaymSec(1);

    LATFbits.LATF0=1;
    LATFbits.LATF1=1;
    LATFbits.LATF2=1;
    LATFbits.LATF3=1;
    LATFbits.LATF5=1;
    LATFbits.LATF4=1;
    LATFbits.LATF6=1;
    delaymSec(1);
}
