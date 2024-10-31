/* 
 * File: Sensors.h
 * Author: William Callahan
 * Comments: Access to temperature and light sensor controls
 * Revision history: 
 */
#ifndef SENSORS_H
#define	SENSORS_H

#include <xc.h>

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */
    
    /**
     * Initializes the ADC controller for use by the {@code readTemperature}
     */
    void initializeAdc(void);
    
    /**
     * Turns on the temperature sensor and reads the temperature
     * 
     * @param portRegister The PORT A, B, or C starting register address (e.g. PORTA)
     * @param toggleRegister The bit in the PORT register to use, MSB
     * @param channelSelect AD Control Channel Select (CHS) Register
     * @return ADC temperature reading
     */
    int readTemperature(volatile unsigned char* portRegister,
        uint8_t toggleRegister,
        uint8_t channelSelect);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* SENSORS_H */

