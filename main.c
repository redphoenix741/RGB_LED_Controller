/*
 * File:   main.c
 * Author: Joem Diente
 *
 * Created on April 4, 2020, 11:48 AM
 */
#include <xc.h>

#define _XTAL_FREQ 8000000

#define GREEN RB0
#define RED RB1
#define BLUE RB2

//RGB_PINOUT
/* RB0 = BLUE
 * RB1 = RED
 * RB2 = GREEN 
 */
void main(void) {
    
    //Pin Init
    TRISCbits.TRISC0 = 0;
    TRISCbits.TRISC1 = 0;
    TRISCbits.TRISC2 = 0;
    
    LATC = 0xFF;
    ANSELC = 0x00;      //Digital
    
    ODCONCbits.ODCC0 = 1;
    ODCONCbits.ODCC1 = 1;
    ODCONCbits.ODCC2 = 1;
    
    while(1)
    {
//        LATCbits.LATC0 ^= 1;
//        LATCbits.LATC1 ^= 1;
//        LATCbits.LATC2 ^= 1;
    }
    return;
}
