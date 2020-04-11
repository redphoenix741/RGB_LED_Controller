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
volatile uint8_t receive_state = 0;
void UART_Rx_IntHandler(void)
{
    UARTReceivedByte = RC1REG;
    
    switch(receive_state)
    {
        case 0:
        {
            if(UARTReceivedByte == 's') 
            {
                UARTBufferIndex = 0;
                receive_state++;
            }
            break;
        }
        case 1:
        {
            if(UARTReceivedByte == '.')
            {
                receive_state++;
            }
            break;
        }
        case 2:
        {
            if(UARTReceivedByte == '.')
            {
                receive_state++;
                UARTBufferIndex = 4;
            }
            else
            {
                //Save to Red
                if(UARTBufferIndex >= 4) UARTBufferIndex = 0;
                UARTBuffer[UARTBufferIndex++] = UARTReceivedByte;
            }
            break;
        }
        case 3:
        {
            if(UARTReceivedByte == '.')
            {
                receive_state++;
                UARTBufferIndex = 8;
            }
            else
            {
                //Save to Green
                if(UARTBufferIndex >= 8) UARTBufferIndex = 4;
                UARTBuffer[UARTBufferIndex++] = UARTReceivedByte;
            }
            break;
        }
        case 4:
        {
            if(UARTReceivedByte == '.')
            {
                receive_state = 0;
                UARTBufferIndex = 0;
                transfer_done = 1;
            }
            else
            {
                //Save to Blue
                if(UARTBufferIndex >= 12) UARTBufferIndex = 8;
                UARTBuffer[UARTBufferIndex++] = UARTReceivedByte;
            }
            break;
        }
        default:
            break;
            
    }
    PIR3bits.RC1IF = 0;
}
void __interrupt() Interrupt_Handler(void)
{
    if(PIR3bits.RC1IF == 1)
    {
        UART_Rx_IntHandler();
    }
}

