/* 
 * File:   Timer0.h
 * Author: moham
 *
 * Created on July 7, 2024, 6:28 PM
 */

#ifndef TIMER0_H
#define	TIMER0_H

#include <xc.h>

// Preload values for Timer0
#define TIMER0_PRELOAD_HIGH (0xC3) // Example value, adjust as needed
#define TIMER0_PRELOAD_LOW (0x27) // Example value, adjust as needed
#define _XTAL_FREQ 16000000 

// Function prototypes
void Timer0_Initialize(void);
void Timer0_ISR(void);
void Timer0_SetCallback(void (*callback)(void));

#endif	/* TIMER0_H */