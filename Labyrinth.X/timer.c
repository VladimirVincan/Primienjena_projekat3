#include "timer.h"
#include <p30fxxxx.h>
#include <p30f4013.h>
#include <stdlib.h>

extern unsigned int timer_us;
extern unsigned int timer_interrupt_us;
extern unsigned int timer_ms, delay_ms; 

void Init_T1(void){
    TMR1 = 0;
	PR1 = MAX_period;
    timer_interrupt_us = 0;
    T1CONbits.TCKPS = 0b10;
	T1CONbits.TCS =0; // 0 = Internal clock (FOSC/4)
	IFS0bits.T1IF = 0; // clear interrupt flag
	IEC0bits.T1IE = 1; // enable interrupt
	T1CONbits.TON = 0; // T1 on 
}

void reset_timer_us(void){
    timer_interrupt_us = 0;
    TMR1 = 0;
}

void start_timer_us(void){
    T1CONbits.TON = 1; 
}

void stop_timer_us(void){
    T1CONbits.TON = 0;
}

void set_timer_interrupt_us(int time_us){
    PR1 = US_period * time_us;
}

void start_measuring_time_us(){
    set_timer_interrupt_us(MAX_period);
    reset_timer_us();
    start_timer_us();
}

unsigned int return_time_measurement_us(){
    stop_timer_us();
    unsigned int ret_val = TMR1;
    reset_timer_us();
    return ret_val;
}

/*********************************/

void Init_T4(void){
    T4CONbits.TON = 0; 
    TMR4 = 0;
    timer_ms = 0;
	PR4 = MS_period;
	T4CONbits.TCS =0; // 0 = Internal clock (FOSC/4)
	IFS1bits.T4IF = 0; // clear interrupt flag
	IEC1bits.T4IE = 1; // enable interrupt
	T4CONbits.TON = 0; // T4 on   
}

void start_timer_ms(void){
    T4CONbits.TON = 1;
}

void stop_timer_ms(void){
    T4CONbits.TON = 0;
}

void Delay_ms (unsigned int time_ms){
    reset_timer_ms();
    start_timer_ms();
    delay_ms = 0;
    while (delay_ms < time_ms);
    stop_timer_ms();
}

void reset_timer_ms(void){
    TMR4 = 0;
    timer_ms = 0;
}

void start_measuring_time_ms(){
    reset_timer_ms();
    delay_ms = 0;
    start_timer_ms();
}

unsigned int return_time_measurement_ms(){
    return TMR4;
}

/*********************************/

void Init_T5(void){
    TMR5 = 0;
	PR5 = US_period;
    timer_interrupt_us = 0;
    //T5CONbits.TCKPS = 0b10;
	T5CONbits.TCS =0; // 0 = Internal clock (FOSC/4)
	IFS1bits.T5IF = 0; // clear interrupt flag
	IEC1bits.T5IE = 1; // enable interrupt
	T5CONbits.TON = 0; // T1 on 
}

void start_timer_5(void){
    T5CONbits.TON = 1;
}

void stop_timer_5(void){
    T5CONbits.TON = 0;
}

void Delay_us (unsigned int time_us){
    reset_timer_5();
    start_timer_5();
    timer_us = 0;
    while (timer_us < time_us);
    stop_timer_5();
}

void reset_timer_5(void){
    TMR5 = 0;
    timer_us = 0;
}