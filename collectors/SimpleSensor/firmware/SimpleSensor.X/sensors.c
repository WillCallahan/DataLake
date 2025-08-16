/*
 * File:   sensors.c
 * Author: wcallahan
 *
 * Created on October 18, 2024, 11:50 PM
 */
#include <xc.h>
#include "settings.h"
#include "sensors.h"

void initializeAdc(void) {
    // Right-justified result and FOSC/8
    ADCON1 = 0b10010000;
}

int readTemperature(volatile unsigned char* portRegister,
        uint8_t toggleRegister,
        uint8_t channelSelect) {
    
    // Turn on the TMP35 sensor
    *portRegister = (unsigned char)(1 << toggleRegister);
    
    // Charge the capacitor, Let the TMP35 sensor startup
    __delay_us(100);
    
    // Enable the ADON ADC conversion bit and select the input channel
    ADCON0 = 1 | (unsigned char)(channelSelect << 2);
    
    // Allow the ADC acquisition to occur, see Table 15-1 with FOSC/8 at 4MHz
    __delay_us(2);
    
    GO_nDONE = 1;
    
    while (GO_nDONE);
    
    int temperature = ((ADRESH << 8) + ADRESL);
    
    
    // Turn off the TMP35 sensor
    *portRegister = (unsigned char)(0 << toggleRegister);
    
    return temperature;
}