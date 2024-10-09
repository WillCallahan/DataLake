#ifndef _SERIAL_H_
#define _SERIAL_H_

volatile struct USART_STATUS {
    unsigned ERR : 1;
    unsigned READING : 1;
    unsigned WRITING : 1;
} uart_status;

typedef void(*usartHandler)(unsigned char charRegister);

void inline handleUsartInterrupt(usartHandler handler);
void putch(char character);
void putPhrase(char phrase[], unsigned int length);

#endif