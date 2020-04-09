/*
 * File:   interrupt.c
 * Author: Joem Diente
 *
 * Created on April 5, 2020, 11:53 AM
 */

#include "interrupt.h"
#include <ctype.h>

void Interrupt_Switch(uint8_t state)
{
    switch(state)
    {
        //Turn Off
        case 0:
        {
            INTCONbits.GIE = 0;
            INTCONbits.PEIE = 0;
            break;
        }
        case 1:
        {
            INTCONbits.PEIE = 1;
            INTCONbits.GIE = 1;
            break;
        }
    }
}
/*
#define UART_RX_SIZE 16
uint8_t UARTBuffer[UART_RX_SIZE];
uint8_t UARTBufferIndex = 0;
uint8_t UARTReceivedByte;
*/
void echo(uint8_t byte)
{
    TX1REG = byte;
    while(TX1STAbits.TRMT == 1);
}
void UART_Rx_IntHandler(void)
{
    UARTReceivedByte = RC1REG;
    
    //Filter Receive
//    if(isxdigit(UARTReceivedByte))
//    {
        //Store then
        UARTBuffer[UARTBufferIndex] = UARTReceivedByte;
        
        //Echo
        echo(UARTReceivedByte);
        
        //Increment Index
        if(UARTBufferIndex < UART_RX_SIZE)
        {
            UARTBufferIndex++;
        }
//    }
//    //isEnter
//    else if(UARTReceivedByte == 0xD)
//    {
//        //Reset Index
//        UARTBufferIndex = 0;
//        EnterKeyPressed = 1;
//        
//        //Echo
//        echo(UARTReceivedByte);
//        echo((uint8_t)'\n');
//    }
//    //isBackspace
//    else if(UARTReceivedByte == 0x7F)
//    {
//        //Check if zero
//        if(UARTBufferIndex != 0)
//        {
//            UARTBufferIndex--;
//        }
//        //Delete
//        UARTBuffer[UARTBufferIndex] = 0;
//       
//        //Echo
//        echo(UARTReceivedByte);
//    }

    PIR3bits.RC1IF = 0;
}
void __interrupt() Interrupt_Handler(void)
{
    if(PIR3bits.RC1IF == 1)
    {
        UART_Rx_IntHandler();
    }
}

