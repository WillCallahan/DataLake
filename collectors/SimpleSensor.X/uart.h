/* 
 * File: string.h
 * Author: William Callahan
 * Comments: String library function
 * Revision history: 
 */

#ifndef _SERIAL_H_
#define _SERIAL_H_

volatile struct USART_STATUS {
    unsigned ERR : 1;
    unsigned READING : 1;
    unsigned WRITING : 1;
} uart_status;

/**
 * Function pointer to a function that will handle data received from the 
 * EUSART Asynchronous module.
 */
typedef void(*usartHandler)(unsigned char charRegister);

/**
 * Checks if an EUSART interrupt occurred and appropriately invokes the 
 * <code>usartHandler</code> if no errors have occurred.
 * @param handler Handler function to execute upon successful receive of a message
 */
void inline handleUsartInterrupt(usartHandler handler);

/**
 * Puts a single character into the EUSART register to be transmitted
 * @param character
 */
void putch(char character);

/**
 * Puts n number of characters into the EUSART register up to the defined
 * <code>length</code>.
 * @param phrase String of characters to transmit
 * @param length Length of string to transmit
 */
void putPhrase(char phrase[], unsigned int length);

#endif