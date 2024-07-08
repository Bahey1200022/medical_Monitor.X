#include "heart.h"


void Heart_Init(void){
    T1CON = 0x31;  // Timer1 with 1:8 prescaler
    TMR1 = 0;  // Clear Timer1 register
    TMR1IF = 0;  // Clear Timer1 interrupt flag
}
//time between peaks
int Calculate_bpm(void){
            unsigned int adcValue = ADC_GetConversion(1);  // Read from ADC channel 1
            uint16_t res1 =adcValue>>6;


    if (res1 > THRESHOLD) {
            // Detected a peak
            currentTime = TMR1;  // Read current timer value
            unsigned int timeDifference = currentTime - lastTime;
            lastTime = currentTime;

            if (timeDifference > 0) {
                bpm = (unsigned int)(60.0 / (timeDifference * (1.0 / (_XTAL_FREQ / 32.0))));  // Calculate BPM
            }

            __delay_ms(300);  // Debounce delay
        }
            return bpm;
}
