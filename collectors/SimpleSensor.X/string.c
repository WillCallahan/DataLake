/*
 * File:   string.c
 * Author: wcallahan
 *
 * Created on October 1, 2024, 7:12 PM
 */


#include <stdarg.h>
#include <string.h>
#include "string.h"

void initializeArrayStringWithNul(char *result, size_t size) {
    for (int i = 0; i < size; i++) {
        result[i] = '\0';
    }
}


__bit strconcat(char *result, size_t size, int num, ...) {
    va_list args;
    va_start(args, num);

    initializeArrayStringWithNul(result, size);

    for (int i = 0; i < num; i++) {
        const char *str = va_arg(args, const char*);

        // Check if we can fit the new string into result
        if (strlen(result) + strlen(str) + 1 <= size) {
            strcat(result, str); // Concatenate the string
        } else {
            return 0;
        }
    }

    va_end(args);
    
    return 1;
}

__bit strcompare(char *a, volatile char b[], size_t length) {
    for (int i = 0; i < length; i++) {
        if (a[i] != b[i]) {
            return 0;
        }
    }
    return 1;
}