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

/* User - Define */
struct
{
    uint8_t red;
    uint8_t grn;
    uint8_t blu;
} rgb;

char colorHex[3];
uint8_t updateRGB = 0;

/*
                         Main application
 */
uint8_t isDataAvailable(void)
{
    while(PIR3bits.RC1IF != 1); //Wait for Received
    PIR3bits.RC1IF = 0;
    return RC1REG;
}
void main(void)
{
    uint8_t state = 0;
    
    // initialize the device
    SYSTEM_Initialize();

    while (1)
    {   
        //Clear Screen
        printf("keep alive\r\n");
        UARTReceivedByte = 0;
        
        switch(state)
        {
            case 0:
            {
                //Wait for period
                printf("Waiting for period (Start)\r\n");
                while(UARTReceivedByte != '.') //Wait until period is received 
                {
                    UARTReceivedByte = isDataAvailable();
                    state++;
                }
                break;
            }
            case 1:
            {
                //Red
                rgb.red = isDataAvailable();
                state++;
                break;
            }
            case 2:
            {
                //Green
                rgb.grn = isDataAvailable();
                state++;
                break;
            }
            case 3:
            {
                //Blue
                rgb.blu = isDataAvailable();
                state++;
                break;
            }
            case 4:
            {
                //Set PWM output to rgb
                printf("Received value: \r\n"
                        "Red: %x,\r\n"
                        "Green: %x,\r\n"
                        "Blue: %x\r\n",
                        rgb.red,rgb.grn,rgb.blu);
                PWM3_LoadDutyValue(rgb.red);
                PWM4_LoadDutyValue(rgb.grn);
                PWM5_LoadDutyValue(rgb.blu);
                state = 0;
                break;
            }
        }
    }
}

/**
 End of File
*/