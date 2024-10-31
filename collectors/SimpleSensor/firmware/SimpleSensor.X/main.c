/*
 * File:   main.c
 * Author: wcallahan
 *
 * Created on September 16, 2024, 10:31 PM
 * 
 * @see https://www.microchip.com/en-us/code-examples Code Examples
 */


#include <xc.h>
#include <stdio.h>
#include <string.h>
#include "settings.h"
#include "uart.h"
#include "lora.h"
#include "string.h"
#include "sensors.h"

#ifndef MAIN_C

// Configuration bits for PIC16F1938
#pragma config FOSC = INTOSC    // Internal oscillator
#pragma config WDTE = 0x3       // Watchdog Timer enabled
#pragma config PWRTE = OFF      // Power-up Timer off
#pragma config MCLRE = ON       // MCLR pin enabled
#pragma config CP = OFF         // Code Protection off
#pragma config CPD = OFF        // Data Code Protection off
#pragma config BOREN = 0x2      // Brown-out Reset enabled when active, disabled during sleep
#pragma config CLKOUTEN = OFF   // CLKOUT function is disabled
#pragma config IESO = OFF       // Internal/External Switch Over mode off
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor disabled
#pragma config WRT = OFF        // Flash Memory Self-Write Protection off
#pragma config PLLEN = OFF      // PLL disabled
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset enabled
#pragma config BORV = LO        // Brown-out Reset Voltage (low)
#pragma config LVP = ON         // Low-Voltage Programming enabled

#pragma config IDLOC0 = 0 // Device ID A
#pragma config IDLOC1 = 0 // Device ID B
#pragma config IDLOC2 = 0 // Software Revision A
#pragma config IDLOC3 = 0 // Software Revision B

#define RX TRISC7
#define TX TRISC6
#define DEBUG_SWITCH RB5
#define BAUD 9600
#define DIVIDER (_XTAL_FREQ / ((4UL * BAUD) - 1)) //Based off manual

#define LORA_ADDRESS 1

#define STR_BUFFER_SIZE 32
#define USART_SUCCESS_READ_HANDLER &handleInterrupt

#define TEMP_PORT PORTA
#define TEMP_0_TOGGLE 0b1
#define TEMP_1_TOGGLE 0b10
#define TEMP_2_TOGGLE 0b100

#define TEMP_0_CHS 0b000
#define TEMP_1_CHS 0b010
#define TEMP_2_CHS 0b100

#endif

void initializePIC(void) {
    // Setup oscillator
    OSCCONbits.IRCF = 0b1101; // 4 MHz HF
    OSCCONbits.SCS = 0b10; // Internal oscillator
    OSCCONbits.SPLLEN = 0; // Disable 4x PLL Clock Multiplier
    
    // Set input/output
    TRISA = 0b00000111; // Set RA<0..2> to input for temperature sensors
    TRISB = 0b00100000; // Set RB5 to input for Debug Switch
    TRISC = 0x00;
    PORTA = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;
    ANSELA = 0b00000111; // Enable RA<0..2> analog input for temperature sensors
    ANSELB = 0x00;
   
    WPUE = 0; //Enable Weak Pull-ups
    WPUB0 = 1; // Set RB5 as a Weak Pull-Up
    
    // Watchdog scaler of 0b10000 - 1:2097152 (64 seconds)
    // Watchdog scaler of 0b01100 - 1:131072 (4 seconds)
    // Watchdog scaler of 0b01010 - 1:32768 (1 seconds)
    WDTCONbits.WDTPS = 0b01100;
}

void initializeUsart() {
    TX = 0;
    RX = 1;
// TODO   SPBRG = DIVIDER;
    SPBRG = 8; // TESTING for 4MHz
    
    SYNC = 0; // Use Asynchronous Mode
    BRGH = 1; //Force High Speed Transmission
    BRG16 = 1; // Disable 16-bit Buad Rate Generator
    
    TXEN = 1; // Enable Transmission Circuitry
    CREN = 1; // Enable Receiver Circuitry
    SPEN = 1; // Enable EUSART
    RCIE = 1; // Enable Receiver Interrupt
    INTCON = 0b11000000; // Enable Peripheral interrupt and Global Interrupts
}

void __interrupt() ISR(void) {
    handleUsartInterrupt(USART_SUCCESS_READ_HANDLER);
}

void blinkLedTimes(int times) {
    __delay_ms(1000);
    for (int i = 0; i != times; i++) {
        RA0 = 1;
        __delay_ms(500);
        RA0 = 0;
        __delay_ms(500);
        CLRWDT();
    }
}

void blinkLedStatus() {
    RA0 = 0;
    if (lora_status.LORA_ERROR_CODE) {
        blinkLedTimes(2);
    }
    if (uart_status.ERR) {
        blinkLedTimes(3);
    }
}

void transmitTemperatureWithDebug(char* outputBuffer, int temperature) {
    if (temperature != INT16_MIN) {
        wakeLora(putPhrase);
        sprintf(outputBuffer, "T%d", temperature);
        sendData(putPhrase, LORA_ADDRESS, outputBuffer);
        temperature = INT16_MIN;
    }
    if (lora_status.LORA_ERROR_CODE > 0) {
        wakeLora(putPhrase);
        sprintf(outputBuffer, "ERR=%d,%d", lora_status.LORA_ERROR_CODE, lora_status.READ_OVERFLOW);
        sendData(putPhrase, LORA_ADDRESS, outputBuffer);
    }
    if (DEBUG_SWITCH == 1) {
        blinkLedStatus();
        RA0 = 0;
    }
}

void readAndTransmitTemperature(char* outputBuffer, uint8_t tempToggle, uint8_t tempChannel) {
    CLRWDT();
    int temperature = readTemperature(&TEMP_PORT, tempToggle, tempChannel);
    transmitTemperatureWithDebug(outputBuffer, temperature);
}

void main(void) {
    initializePIC();
    initializeAdc();
    initializeUsart();
    initializeLora(putPhrase, LORA_ADDRESS);
    
    char outputBuffer[8];
    
    strcpy(outputBuffer, "INIT");
    sendData(putPhrase, LORA_ADDRESS, outputBuffer);
    
    while (1) {
        if (DEBUG_SWITCH == 1) {
            RA0 = 1; // Blink an LED for status
        }

        readAndTransmitTemperature(outputBuffer, TEMP_0_TOGGLE, TEMP_0_CHS);
        __delay_us(500); // Wait before the next read
        readAndTransmitTemperature(outputBuffer, TEMP_1_TOGGLE, TEMP_1_CHS);
        __delay_us(500); // Wait before the next read
        readAndTransmitTemperature(outputBuffer, TEMP_2_TOGGLE, TEMP_2_CHS);
        
        sleepLora(putPhrase);
        SLEEP();
        NOP();
    }
}
