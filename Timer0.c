#include "Timer0.h"

static void (*Timer0_Callback)(void) = 0; // Function pointer for the callback

void Timer0_Initialize(void) {
    
     // Stop the timer
    T0CONbits.TMR0ON = 0;
    T0CONbits.PSA = 0;       // Enable prescaler
    T0CONbits.T0CS = 0;      // Use internal instruction cycle clock (Fosc/4)

    T0CONbits.T0PS = 0b111;   // Set Timer0 prescaler to 1:256
    T0CONbits.T08BIT = 0;     // Set Timer0 to 16-bit mode
    TMR0H = TIMER0_PRELOAD_HIGH; // Load high byte
    TMR0L = TIMER0_PRELOAD_LOW;  // Load low byte
    INTCONbits.TMR0IF = 0;    // Clear Timer0 interrupt flag
    INTCONbits.TMR0IE = 1;    // Enable Timer0 interrupt
    T0CONbits.TMR0ON = 1;     // Enable Timer0
}

void Timer0_ISR(void) {
    if (INTCONbits.TMR0IF) {
        INTCONbits.TMR0IF = 0;     // Clear Timer0 interrupt flag
        TMR0H = TIMER0_PRELOAD_HIGH; // Reload Timer0 high byte
        TMR0L = TIMER0_PRELOAD_LOW;  // Reload Timer0 low byte
        if (Timer0_Callback) {
            Timer0_Callback();     // Call the user-defined callback function
        }
    }
}

void Timer0_SetCallback(void (*callback)(void)) {
    Timer0_Callback = callback;    // Set the user-defined callback function
}
