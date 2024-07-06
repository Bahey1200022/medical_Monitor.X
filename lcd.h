/* 
 * File:   lcd.h
 * Author: moham
 *
 * Created on July 5, 2024, 6:57 AM
 */

#ifndef LCD_H
#define	LCD_H
#include "mcc_generated_files/uart/eusart.h"
#include <xc.h>
#define _XTAL_FREQ 4000000  // Define the clock frequency for delay functions

void LCD_Init(void);
void LCD_Command(uint8_t cmd );
void LCD_WriteChar(unsigned char data);
void LCD_WriteString(const char *str);
#endif	/* LCD_H */

