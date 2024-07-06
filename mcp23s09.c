#include "mcp23s09.h"
#include "spi.h"

#define MCP23S09_CS LATDbits.LATD0

#define MCP23S09_ADDR 0x40
//The SPI write operation is started by lowering CS. The
/*write command (slave address with R/W bit cleared) is
then clocked into the device. The opcode is followed by
an address and at least one data byte.*/

void MCP23S09_Init(void) {
    // Set control pin as output
    TRISDbits.TRISD0 = 0; // CS
    SPI_Init();

    // Initialize MCP23S09
    MCP23S09_Write(0x0A, 0xFF); //OLAT set

    MCP23S09_Write(0x00, 0x00); // IODIR - Set all as outputs
    MCP23S09_Write(0x06,0xFF);
    
}

void MCP23S09_Write(uint8_t reg, uint8_t data) {
    MCP23S09_CS = 0; // Select MCP23S09
    SPI_Write(0b01000000); // Address + Write 01000000
    SPI_Write(reg); // Register address
//
   SPI_Write(data); // Data
   
  
       
   MCP23S09_CS = 1; // Deselect MCP23S09
   
   
           }


