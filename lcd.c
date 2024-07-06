#include "lcd.h"
#include "mcp23s09.h"
#include "spi.h"
void LCD_Command(uint8_t cmd) {
    // Send higher nibble (D7-D4) with RS = 0 (Command mode)
    MCP23S09_Write(0x09, ((cmd & 0xF0) | 0x04));  // Set RS to 0, EN to 1
    __delay_us(1);  // Minimum EN pulse width
    MCP23S09_Write(0x09, (cmd & 0xF0));     // Set RS to 0, EN to 0
    __delay_ms(2);  // Delay after command (adjust as per LCD datasheet)

    // Send lower nibble (D3-D0) with RS = 0 (Command mode)
    MCP23S09_Write(0x09, (((cmd << 4) & 0xF0) | 0x04));     // Set RS to 0, EN to 1
    __delay_us(1);  // Minimum EN pulse width
    MCP23S09_Write(0x09, ((cmd << 4) & 0xF0));        // Set RS to 0, EN to 0
    __delay_ms(2);  // Delay after command (adjust as per LCD datasheet)
}

void LCD_WriteChar(uint8_t data) {
    // Send higher nibble (D7-D4) with RS = 1 (Data mode)
    MCP23S09_Write(0x09,( (data & 0xF0) | 0x05));   // Set RS to 1, EN to 1
    __delay_us(1);  // Minimum EN pulse width
    MCP23S09_Write(0x09, ((data & 0xF0) |0x01)); // Set RS to 1, EN to 0
    __delay_us(200);  // Delay after data write (adjust as per LCD datasheet)

    // Send lower nibble (D3-D0) with RS = 1 (Data mode)
    MCP23S09_Write(0x09, (((data << 4) & 0xF0) | 0x05));  // Set RS to 1, EN to 1
    __delay_us(1);  // Minimum EN pulse width
    MCP23S09_Write(0x09, (((data << 4) & 0xF0) |0x01)); // Set RS to 1, EN to 0
    __delay_ms(2);  // Delay after data write (adjust as per LCD datasheet)
}

void LCD_WriteString(const char *str) {
    while (*str) {
        LCD_WriteChar(*str++);
    }
}

void LCD_Init(void) {
    MCP23S09_Init();
    __delay_ms(20);  // LCD Power ON delay always >15ms

    LCD_Command(0x33);
    __delay_ms(5);
    LCD_Command(0x32);  // Send for 4 bit initialization of LCD
    __delay_ms(5);
    LCD_Command(0x28);  // 2 line, 5*7 matrix in 4-bit mode
    __delay_ms(5);
    LCD_Command(0x0C);  // Display on cursor off
    __delay_ms(5);
    LCD_Command(0x06);  // Increment cursor (shift cursor to right)
    __delay_ms(5);
    LCD_Command(0x01);  // Clear display screen
    __delay_ms(5);
}