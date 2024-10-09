/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef _LORA_HEADER_TEMPLATE_H_
#define	_LORA_HEADER_TEMPLATE_H_

#include <xc.h> // include processor files - each processor file is guarded.  

// TODO Insert appropriate #include <>

// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations

// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 
    
    // region Lora AT Commands
    // All tokens follow the L(TYPE)_(TEXT) syntax
    // TYPE may be one of the following
    // <ul>
    //      <li>C - Command</li>
    //      <li>S - Set a setting</li>
    //      <li>R - Response</li>
    //      <li>Q - Question</li>
    //      <li>D - Data response</li>
    //      <li>L - Listen/receive data command</li>
    //      <li>E - Error response code</li>
    //      <li>V - Constant value</li>
    // </ul>
    // endregion

    
#define LC_AT "AT"
#define LR_OK "+OK"
// Skip the "AT" portion in the response when comparing the command send and the response
#define LR_COMMAND_OFFSET_INDEX 1
    
#define LC_RESET "AT+RESET"
#define LR_RESET_RST "+RESET"
#define LR_RESET_RDY "+READY"
    
#define LS_MODE "AT+MODE="
#define LR_MODE LR_OK
#define LV_MODE_TRANSEIVE 0
#define LV_MODE_SLEEP 1
#define LV_MODE_SMART 2
    
#define LQ_MODE "AT+MODE?"
#define LD_MODE "+MODE="
    
#define LS_IPR "AT+IPR="
#define LR_IPR LR_OK
    
#define LQ_IPR "AT+IPR?"
#define LD_IPR "+IPR="
    
#define LS_BAND "AT+BAND="
#define LR_BAND LR_OK
    
#define LQ_BAND "AT+BAND?"
#define LD_BAND "AT+BAND="

    // See https://unsigned.io/understanding-lora-parameters/ for calculations
#define LS_PARAM "AT+PARAMETER="
#define LR_PARAM LR_OK
#define LV_PARAM_SF_125KHZ_7 7
#define LV_PARAM_SF_125KHZ_8 8
#define LV_PARAM_SF_125KHZ_9 9
#define LV_PARAM_SF_250KHZ_7 7
#define LV_PARAM_SF_250KHZ_8 8
#define LV_PARAM_SF_250KHZ_9 9
#define LV_PARAM_SF_250KHZ_10 10
#define LV_PARAM_SF_500KHZ_7 7
#define LV_PARAM_SF_500KHZ_8 8
#define LV_PARAM_SF_500KHZ_9 9
#define LV_PARAM_SF_500KHZ_10 10
#define LV_PARAM_SF_500KHZ_11 11
#define LV_PARAM_BW_125KHZ 7
#define LV_PARAM_BW_250KHZ 8
#define LV_PARAM_BW_500KHZ 9
#define LV_PARAM_CR_4_5 1
#define LV_PARAM_CR_4_6 2
#define LV_PARAM_CR_4_7 3
#define LV_PARAM_CR_4_8 4
        
#define LQ_PARAM "AT+PARAMTER?"
#define LD_PARAM "+PARAMETER="
    
#define LS_ADDRESS "AT+ADDRESS="
#define LR_ADDRESS LR_OK
    
#define LQ_ADRESS "AT+ADDRESS?"
#define LD_ADRESS "+ADRESS="
    
#define LS_NETID "AT+NETWORKID="
#define LR_NETID LR_OK
    
#define LQ_NETID "AT+NETWORKID?"
#define LD_NETID "+NETWORKID="
    
#define LS_CPIN "AT+CPIN="
#define LR_CPIN LR_OK
    
#define LQ_CPIN "AT+CPIN?"
#define LD_CPIN "CPIN="
#define LD_CPIN_NOPASS "No Password!"
    
#define LS_CRFOP "AT+CRFOP="
#define LR_CRFOP LR_OK
    
#define LQ_CRFOP "AT+CRFOP?"
#define LD_CRFOP "+CRFOP="
    
#define LC_SEND "AT+SEND="
#define LR_SEND LR_OK
    
#define LQ_SEND "AT+SEND?"
#define LD_SEND "+SEND="
    
#define LL_RCV "+RCV"
#define LR_RCV "+RCV="
    
#define LQ_UID "AT+UID?"
#define LD_UID "UID="
    
#define LQ_VER "AT+VER?"
#define LD_VER "+VER="
    
#define LC_FACTORY "AT+FACTORY"
#define LR_FACTORY "+FACTORY"
    
    
#define LR_ERR "+ERR="
#define LR_ERR_ENT_MIS 1
#define LR_ERR_NOT_AT 2
#define LR_ERR_UNKN_CMD 4
#define LR_ERR_SEND_LEN 5
#define LR_ERR_TX_TIME 10
#define LR_ERR_CRC_ERR 12
#define LR_ERR_RX_240_BYTES 13
#define LR_ERR_MEM_WRT 14
#define LR_ERR_UNKWN 15
#define LR_ERR_TX_INCMPLT 17
#define LR_ERR_PREM_DENY 18
#define LR_ERR_RX_HEAD 19
#define LR_ERR_RX_SMRT_TIME_DENY 20
    
#define LORA_DATA_BUFFER_SIZE 32
    
#ifndef _XTAL_FREQ
//#define _XTAL_FREQ 31250
#define _XTAL_FREQ 4000000
#endif

    typedef void(*transmitData)(char data[], unsigned int length);
    
    volatile struct LORA_STATUS {
        volatile unsigned WAIT_RESPONSE : 1;
        volatile unsigned PARSING : 1;
        volatile unsigned SUCCESS : 1;
        volatile unsigned READ_TIMEOUT : 1;
        volatile unsigned READ_OVERFLOW : 1;
        volatile unsigned WRITE_OVERFLOW : 1;
        volatile unsigned LORA_ERROR_CODE : 5;
    } lora_status;
    
    static volatile unsigned short LORA_ERROR_COUNT;
    static volatile short LORA_PARSE_INDEX;
    static volatile char LORA_R_DATA[LORA_DATA_BUFFER_SIZE];
    
    void handleInterrupt(unsigned char data);
    
    __bit isCompleteParse();
    
    __bit isErrorParse();
    
    char getErrorCode();
    
    void sendData(transmitData transmit, char address, char data[]);
    
    void sleepLora(transmitData transmit);
    
    void wakeLora(transmitData transmit);
    
    void initializeLora(transmitData transmit, char address);
    
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

