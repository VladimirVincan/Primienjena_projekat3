/* 
 * File:   uart.h
 * Author: Vladimir Vincan EE5-2015
 *
 * Created on April 1, 2019, 2:25 AM
 */

#ifndef UART_H
#define	UART_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <p30fxxxx.h>
#define BAUD_RATE_1200 0x0207
#define BAUD_RATE_9600 0x0040

void initUART1(void);
void WriteUART1_char(unsigned int data);
void WriteUART1_int(unsigned int data);
void WriteUART1_string(register const char *str);

void initUART2(void);
void WriteUART2_char(unsigned int data);
void WriteUART2_int(unsigned int data);
void WriteUART2_string(register const char *str);

#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */
