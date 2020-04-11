/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.80.0
        Device            :  PIC16F15356
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include "interrupt.h"
#include <string.h>

/* User - Define */
struct
{
    uint16_t red;
    uint16_t grn;
    uint16_t blu;
} rgb;


/*
                         Main application
 */
uint16_t string_to_decimal(uint8_t *buffer)
{
    char temp_buffer[4];
    memcpy(temp_buffer,buffer,4);
    return atoi(temp_buffer);
}
void main(void)
{
    uint8_t state = 0;
    
    // initialize the device
    SYSTEM_Initialize();
    
    //Turn On Interrupt
    Interrupt_Switch(1);

    while (1)
    {   
        if(transfer_done == 1)
        {
            //Disable UART Interrupt
            PIE3bits.RC1IE = 0;
            
            //Reset Flag
            transfer_done = 0;
            
            //Parse Buffer
            rgb.red = string_to_decimal(&UARTBuffer[0]);
            rgb.grn = string_to_decimal(&UARTBuffer[4]);
            rgb.blu = string_to_decimal(&UARTBuffer[8]);
            
            //Set PWM output to rgb
            PWM3_LoadDutyValue(rgb.red);
            PWM4_LoadDutyValue(rgb.grn);
            PWM5_LoadDutyValue(rgb.blu);
            
            //Clear Buffers
            memset(UARTBuffer,0,16);
            
            //Enable UART Interrupt
            PIE3bits.RC1IE = 1;
        }
    }
}

/**
 End of File
*/