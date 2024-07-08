 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
*/

/*
© [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"
#include "spi.h"
#include "lcd.h"
#include "mcp23s09.h"
#include "Timer0.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "../xc.h"
/*
    Main application
*/
volatile int overflow_count = 0;


void Timer0_UserCallback(void) {
    overflow_count++;
    if (overflow_count >= 10) {
        overflow_count = 0;
         char str[6]; // Adjust the size if needed
         adc_result_t adcValue = ADC_GetConversion(0);
       uint16_t res =adcValue>>6;
       int temp = (int)((float)res / 1023.0 * 500);
        uint8_t temp_uint8 = (uint8_t)temp; // Cast temp to uint8_t

        // Convert temperature to string
        sprintf(str, "Temp: %u\r\n", temp_uint8);

        // Send the string via EUSART
        // Convert the ADC value to a string

        
        EUSART_WriteString(str);
        __delay_ms(100);
        

    }
}

void __interrupt() ISR(void) {

    Timer0_ISR();
}

int main(void)
{
    SYSTEM_Initialize();
   
    TRISCbits.TRISC2=0;   /// int debug not working 

    

    


    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts 
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts 
    // Use the following macros to: 

    // Enable the Global Interrupts 
    INTERRUPT_GlobalInterruptEnable(); 

    // Disable the Global Interrupts 
    //INTERRUPT_GlobalInterruptDisable(); 

    // Enable the Peripheral Interrupts 
    INTERRUPT_PeripheralInterruptEnable(); 

    // Disable the Peripheral Interrupts 
    //INTERRUPT_PeripheralInterruptDisable(); 
    
   LCD_Init();

LCD_WriteString("Monitor Start");
__delay_ms(400);
   LCD_Command(0x01);  // Clear display screen

 char str[6]; // Adjust the size if needed

 Timer0_Initialize();
 Timer0_SetCallback(Timer0_UserCallback);
    while(1)
    {
       adc_result_t adcValue = ADC_GetConversion(0);
       uint16_t res =adcValue>>6;
       int temp = (int)((float)res / 1023.0 * 500);
       
        // Convert the ADC value to a string

        sprintf(str, "%u",temp);
        

        LCD_WriteString("T : ");
        LCD_WriteString(str);

    __delay_ms(1000);
    LCD_Command(0x01);  // Clear display screen
    __delay_ms(100);


    }    
}