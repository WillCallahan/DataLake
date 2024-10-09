#include <xc.h>
#include "uart.h"

void inline handleUsartInterrupt(usartHandler successHandler) {
    if (!RCIF) {
        return;
    }
    
    if (OERR) { // Overrun Error
        SPEN = CREN = 0;
        SPEN = CREN = 1;
        uart_status.ERR = 1;
        return;
    }
    if (FERR) { //Framing Error
        SPEN = CREN = 0;
        SPEN = CREN = 1;
        uart_status.ERR = 1;
        return;
    }
    
    uart_status.ERR = 0;
    uart_status.READING = 1;
    successHandler(RCREG);
}

void putch(char byte)
{
	/* output one byte */
	while(!TXIF) {	/* set when register is empty */
		continue;
    }
	TXREG = byte;
}

void putPhrase(char phrase[], unsigned int length) {
    for (unsigned int i = 0; i < length; i++) {
        putch(phrase[i]);
    }
}
