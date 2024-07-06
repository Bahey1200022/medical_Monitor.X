/* 
 * File:   mcp23s09.h
 * Author: moham
 *
 * Created on July 5, 2024, 6:54 AM
 */

#ifndef MCP23S09_H
#define	MCP23S09_H

#include <xc.h>
#include "mcc_generated_files/uart/eusart.h"
#define _XTAL_FREQ 16000000  // Define the clock frequency for delay functions

void MCP23S09_Init(void);
void MCP23S09_Write(uint8_t reg, uint8_t data);


#endif	/* MCP23S09_H */

