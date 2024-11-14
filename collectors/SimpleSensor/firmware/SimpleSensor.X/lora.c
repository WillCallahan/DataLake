/*
 * File:   lora.c
 * Author: wcallahan
 *
 * Created on September 30, 2024, 1:22 AM
 */


#include <xc.h>
#include <string.h>
#include <stdio.h>
#include "settings.h"
#include "lora.h"
#include "string.h"

#define LR_COMMAND_BUFFER_SIZE 32
#define LR_COMMAND_AIR_TIME_PER_BYTE_MS 145 // Based on a SF=11, BW=500MHz
#define LR_COMMAND_DEFAULT_WAIT_MS 500

void handleInterrupt(unsigned char character) {
    lora_status.WAIT_RESPONSE = 0;
    
    if (character == '+') {
        LORA_PARSE_INDEX = 0;
        lora_status.PARSING = 1;
    }
    else if (LORA_PARSE_INDEX + 1 >= LORA_DATA_BUFFER_SIZE) {
        lora_status.PARSING = 0;
        lora_status.READ_OVERFLOW = 1;
    }
    else if (character == '\n') {
        lora_status.PARSING = 0;
        lora_status.SUCCESS = 1;
        LORA_R_DATA[LORA_PARSE_INDEX + 1] = '\0';
    }
    else if (lora_status.PARSING == 1) {
        LORA_PARSE_INDEX += 1;
    }
    
    LORA_R_DATA[LORA_PARSE_INDEX] = character;
}

void waitResponse(int timeout) {
    int maxWait = timeout;
    while (lora_status.WAIT_RESPONSE && maxWait > 0) {
        __delay_ms(1);
        maxWait--;
    }
    if (maxWait == 0) {
        lora_status.LORA_ERROR_CODE = 1;
        return;
    }
    
    maxWait = timeout;
    while (lora_status.PARSING) {
        __delay_ms(1);
        maxWait--;
        continue;
    }
    if (maxWait == 0) {
        lora_status.READ_TIMEOUT = 1;
        return;
    }
    
    int isError = strcompare(LR_ERR, LORA_R_DATA, 5);
    if (isError) {
        LORA_ERROR_COUNT++;
    } else {
        CLRWDT();
    }
}

int getTrasmissionTime(int payloadSize) {
    const int additionalBytes = 8; // Additional bytes introduced by LoRa protocol
    int totalTime = (payloadSize + additionalBytes) * LR_COMMAND_AIR_TIME_PER_BYTE_MS;
    return totalTime;
}

__bit waitResponseExact(char* response, int timeout) {
    size_t isMatch = strcompare(response, LORA_R_DATA, strlen(response));
    
    while (!isMatch && timeout > 0) {
        int isError = strcompare(LR_ERR, LORA_R_DATA, 5);
        if (isError) {
            return 0;
        }
        
        isMatch = strcompare(response, LORA_R_DATA, strlen(response));
        __delay_ms(1);
        timeout--;
    }
    
    CLRWDT();
    return isMatch > 0 ? 1 : 0;
}

void transmitWithEol(transmitData transmit, char data[], unsigned int length) {
    if (length + 1 > LR_COMMAND_BUFFER_SIZE) {
        lora_status.WRITE_OVERFLOW = 1;
        return;
    }
    lora_status.WRITE_OVERFLOW = 0;
    
    data[length] = '\r';
    data[length + 1] = '\n';
    data[length + 2] = '\0';
    
    transmit(data, strlen(data));
}

void sendData(transmitData transmit, char address, char data[]) {
    char command[LR_COMMAND_BUFFER_SIZE];
    unsigned int currentIndex = 0;
    
    strcpy(command, LC_SEND);
    currentIndex = strlen(command);
    sprintf(&command[currentIndex], "%d", address);
    currentIndex = strlen(command);
    command[currentIndex++] = ',';
    sprintf(&command[currentIndex], "%d", strlen(data));
    currentIndex = strlen(command);
    command[currentIndex++] = ',';
    strcpy(&command[currentIndex], data);
    
    transmitWithEol(transmit, command, strlen(command));
    int transmissionTimeout = getTrasmissionTime((int)strlen(data));
    waitResponseExact(LR_OK, transmissionTimeout);
}

void sleepLora(transmitData transmit) {
    char command[LR_COMMAND_BUFFER_SIZE];
    strconcat(command, LR_COMMAND_BUFFER_SIZE, 2, LS_MODE, "1");
    transmitWithEol(transmit, command, strlen(command));
    waitResponseExact(LR_OK, LR_COMMAND_DEFAULT_WAIT_MS);
}

void wakeLora(transmitData transmit) {
    char command[LR_COMMAND_BUFFER_SIZE];
    strconcat(command, LR_COMMAND_BUFFER_SIZE, 2, LS_MODE, "0");
    transmitWithEol(transmit, command, strlen(command));
    waitResponseExact(LR_OK, LR_COMMAND_DEFAULT_WAIT_MS);
}

void initializeLora(transmitData transmit, char address) {
    // Delay for 100ms for LORA RYLR998 Initialization
    __delay_ms(100);
    
    char command[LR_COMMAND_BUFFER_SIZE];
    
    strcpy(command, LC_RESET);
    transmitWithEol(transmit, command, strlen(command));
    __delay_ms(100); // Wait for the reset to complete
    waitResponseExact(LR_RESET_RDY, LR_COMMAND_DEFAULT_WAIT_MS);
    
    strcpy(command, LS_ADDRESS);
    sprintf(&command[strlen(command)], "%d", address);
    transmitWithEol(transmit, command, strlen(command));
    waitResponse(LR_COMMAND_DEFAULT_WAIT_MS);
    __delay_ms(100);
    
    strconcat(command, LR_COMMAND_BUFFER_SIZE, 2, LS_NETID, "18");
    transmitWithEol(transmit, command, strlen(command));
    waitResponse(LR_COMMAND_DEFAULT_WAIT_MS);
    __delay_ms(100);
    
    strconcat(command, LR_COMMAND_BUFFER_SIZE, 2, LS_BAND, "915000000");
    transmitWithEol(transmit, command, strlen(command));
    waitResponse(LR_COMMAND_DEFAULT_WAIT_MS);
    __delay_ms(100);
    
    strconcat(command, LR_COMMAND_BUFFER_SIZE, 2, LS_PARAM, "11,9,4,12");
    transmitWithEol(transmit, command, strlen(command));
    waitResponse(LR_COMMAND_DEFAULT_WAIT_MS);
    __delay_ms(100);

    strconcat(command, LR_COMMAND_BUFFER_SIZE, 2, LS_CRFOP, "13");
    transmitWithEol(transmit, command, strlen(command));
    waitResponseExact(LR_OK, LR_COMMAND_DEFAULT_WAIT_MS);
    __delay_ms(100);
    
    strconcat(command, LR_COMMAND_BUFFER_SIZE, 2, LS_MODE, "0");
    transmitWithEol(transmit, command, strlen(command));
    waitResponseExact(LR_OK, LR_COMMAND_DEFAULT_WAIT_MS);
    __delay_ms(100);
}