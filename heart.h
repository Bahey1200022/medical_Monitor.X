/* 
 * File:   heart.h
 * Author: moham
 *
 * Created on July 8, 2024, 4:36 PM
 */

#ifndef HEART_H
#define	HEART_H
#define _XTAL_FREQ 16000000
#define THRESHOLD 450  // Set an appropriate threshold for peak detection
#include "mcc_generated_files/adc/adc.h"
#include "../xc.h"
static volatile unsigned int lastTime = 0;
static volatile unsigned int currentTime = 0;
static volatile unsigned int bpm = 0;

void Heart_Init(void); //timer init ??

int Calculate_bpm(void);

#endif	/* HEART_H */

