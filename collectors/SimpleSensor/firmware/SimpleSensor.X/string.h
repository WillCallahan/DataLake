/* 
 * File: string.h
 * Author: William Callahan
 * Comments: String library function
 * Revision history: 
 */

#ifndef _STRING_INTERNAL_H_
#define	_STRING_INTERNAL_H_

#include <xc.h>
#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */
    
    /**
     * Concatenates a variable number of string arguments into a single string.
     * 
     * @param result Target buffer size
     * @param size Maximum size of the target buffer
     * @param num Number of string arguments
     * @param ... Variable string arguments, matching the <code>num</code> argument
     * @return Whether the operation completed successfully
     */
    __bit strconcat(char *result, size_t size, int num, ...);
    
    /**
     * Compares two strings for equality up to a maximum number of characters.
     * 
     * @param a String array A
     * @param b String array B
     * @param length Number of characters, starting from address 0, to compare
     * @return Whether String A and B match up to the length
     */
    __bit strcompare(char *a, volatile char b[], size_t length);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* _STRING_INTERNAL_H_ */

