#include "timer.h"
#include <p30fxxxx.h>
#include <p30f4013.h>
#include <stdlib.h>

extern int timer_us, timer_ms;
extern int delay_us, delay_ms; 

void Init_T1(void){
    TMR1 = 0;
    //timer_us = 0;
	PR1 = TMR1_period;
	T1CONbits.TCS =0; // 0 = Internal clock (FOSC/4)
	IFS0bits.T1IF = 0; // clear interrupt flag
	IEC0bits.T1IE = 1; // enable interrupt
    WriteUART1_string("stane ");
	T1CONbits.TON = 1; // T1 on 
    WriteUART1_string("radi ");
}

void Delay_us (int time){
    delay_us = 0;
    while (delay_us < time);
}

void reset_timer_us(void){
    TMR1 = 0;
    timer_us = 0;
}

int read_timer_us(void){
    return timer_us;
}

/*********************************/

void Init_T4(void){
    T4CONbits.TON = 0; 
    TMR4 = 0;
    //timer_ms = 0;
	PR4 = TMR4_period;
	T4CONbits.TCS =0; // 0 = Internal clock (FOSC/4)
	IFS1bits.T4IF = 0; // clear interrupt flag
	IEC1bits.T4IE = 1; // enable interrupt
	T4CONbits.TON = 1; // T4 on   
}

void Delay_ms (int time){
    delay_ms = 0;
    while (delay_ms < time);
}

void reset_timer_ms(void){
    TMR4 = 0;
    timer_ms = 0;
}

int read_timer_ms(void){
    return timer_ms;
}