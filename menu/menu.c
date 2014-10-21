#include <plib.h>

//#include "../drivers/lcd/lcdOutputStream.h"
#include "../common/io/outputStream.h"
#include "menu.h"

/*************************************************************
 * menu_P						     *								*
 * Affiche le menu Principal                                 *
 * @param  :                                                 *
 * @return : none					     *
 ************************************************************/
void menu_P(OutputStream* outputStream){
    ClrGraphLCD_24064();
    // parti superieur
    line (0,7,239,7);
    line (136,0,136,6);
    line (110,0,110,6);
    setCursorPosition(0,0);
    appendString(outputStream,"F4DEB");

    //parti inferieur
    line (0,55,239,55);
    line (40,56,40,63);
    line (80,56,80,63);
    line (120,56,120,63);
    line (160,56,160,63);
    line (200,56,200,63);

    setCursorPosition(7,1);
    appendString(outputStream,"RADIO MESURE SETUP  TEST");
    
}