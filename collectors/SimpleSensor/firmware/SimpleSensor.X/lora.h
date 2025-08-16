/* 
 * File: Lora.c
 * Author: William Callahan
 * Comments: EUSART Communication with the RYLR998
 * Revision history:
 * - Initial Support 
 */

#ifndef _LORA_HEADER_TEMPLATE_H_
#define	_LORA_HEADER_TEMPLATE_H_

#include <xc.h>

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 
    
    // Lora AT Commands
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

    
#define LC_AT "AT"
#define LR_OK "+OK"
    
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
    
    /**
     * Handles an interrupt for an incoming message from the transceiver
     * @param data Character from receiver
     */
    void handleInterrupt(unsigned char data);
    
    /**
     * Whether parsing has completed based on possible response codes
     * @return If the parsing is complete
     */
    __bit isCompleteParse();
    
    /**
     * Whether an error occurred during parsing of a response
     * @return If there was an error during parsing
     */
    __bit isErrorParse();
    
    /**
     * Gets the decoded error code provided from the Lora transceiver
     * @return 
     */
    char getErrorCode();
    
    /**
     * Sends NUL terminated data to a target Lora Address
     * 
     * @param transmit Function used to transmit data
     * @param address Address of the target Lora device
     * @param data Data to send, terminated with the NUL character
     */
    void sendData(transmitData transmit, char address, char data[]);
    
    /**
     * Puts the Lora transceiver in sleep mode for power savings
     * @param transmit Function used to transmit data
     */
    void sleepLora(transmitData transmit);
    
    /**
     * Wakes the Lora transceiver from sleep mode to be able to transmit
     * @param transmit Function used to transmit
     */
    void wakeLora(transmitData transmit);
    
    /**
     * Initializes the Lora transceiver
     * 
     * @param transmit Function used to transmit
     * @param address Address of this device
     */
    void initializeLora(transmitData transmit, char address);
    
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* _LORA_HEADER_TEMPLATE_H_ */

