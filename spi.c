#include "spi.h"

#include "spi.h"

void SPI_Init(void) {
    TRISCbits.TRISC3 = 0; // SCK as output
    TRISCbits.TRISC5 = 0; // SDO as output
    SSPCON1 = 0x20; // Enable SPI, Master mode, clock = FOSC/4
    SSPSTAT = 0x00;
}

void SPI_Write(uint8_t data) {
    SSPBUF = data;
    while (!SSPSTATbits.BF);

}

