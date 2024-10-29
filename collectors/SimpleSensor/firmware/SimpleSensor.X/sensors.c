/*
 * File:   sensors.c
 * Author: wcallahan
 *
 * Created on October 18, 2024, 11:50 PM
 */
#include <xc.h>
#include "settings.h"
#include "sensors.h"

void initializeAdc() {
    ADCON1 = 0b10010000;
}

int readTemperature(volatile unsigned char* portRegister,
        uint8_t toggleRegister,
        uint8_t channelSelect) {
    
    // Turn on the TMP35 sensor
    *(portRegister + toggleRegister) = 1;    
    
    // Let the TMP35 sensor startup
    __delay_us(50);
    
    ADCON0 = 1 & (channelSelect << 2);
    
    // Allow the ADC acquisition to occur
    __delay_us(10);
    
    while (GO_nDONE);
    
    int temperature = ((ADRESH << 8) + ADRESL);
    
    
    // Turn off the TMP35 sensor
    *(portRegister + toggleRegister) = 0;
    
    return temperature;
}