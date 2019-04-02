/* 
 * File:   timer.h
 * Author: Z1
 *
 * Created on April 2, 2019, 1:47 AM
 */

#ifndef TIMER_H
#define	TIMER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <p30fxxxx.h>
#include <p30f4013.h>
#include <stdlib.h>
#include "uart.h"

#define TMR1_period 10 // Fosc = 10MHz, 1/Fosc = 0.1us, 0.1us * 10 = 1us 
#define TMR4_period 10000 // Fosc = 10MHz, 1/Fosc = 0.1us, 0.1us * 10000 = 1ms     
    
void Init_T1(void);
void Delay_us (int time); // utilized with T1
void reset_timer_us(void);
int read_timer_us(void);

void Init_T4(void);
void Delay_ms (int time); // utilized with T4
void reset_timer_ms(void);
int read_timer_ms(void);

#ifdef	__cplusplus
}
#endif

#endif	/* TIMER_H */

