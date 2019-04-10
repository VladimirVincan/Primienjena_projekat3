/* 
 * File:   timer.h
 * Author: Vladimir Vincan EE5-2015
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

#define US_period 10 // Fosc = 10MHz, 1/Fosc = 0.1us, 0.1us * 10 = 1us 
#define MS_period 10000 // Fosc = 10MHz, 1/Fosc = 0.1us, 0.1us * 10000 = 1ms
#define MAX_period 0xffff
    
void Init_T1(void);
//void Delay_us (unsigned int time_us); // utilized with T5
void reset_timer_us(void);
void start_timer_us(void);
void stop_timer_us(void);
void set_timer_interrupt_us(int time_us);
void start_measuring_time_us();
unsigned int return_time_measurement_us();

void Init_T4(void);
void Delay_ms (unsigned int time_ms); // utilized with T4
void start_timer_ms(void);
void stop_timer_ms(void);
void reset_timer_ms(void);
void start_measuring_time_ms();
unsigned int return_time_measurement_ms();

void Init_T5(void);
void Delay_us (unsigned int time_us); // utilized with T5
void start_timer_5(void);
void stop_timer_5(void);
void reset_timer_5(void);

#ifdef	__cplusplus
}
#endif

#endif	/* TIMER_H */
