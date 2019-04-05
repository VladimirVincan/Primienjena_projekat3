#include <p30fxxxx.h>
#include <p30f4013.h>
#include "motor.h"
#include "uart.h"
#include "sensor.h"
#include "timer.h"
#include "adc.h"

_FOSC(CSW_FSCM_OFF & XT_PLL4);
_FWDT(WDT_OFF);

#define MAX_TIMER_VAL 32000
#define TIMES_MEASURED 1

unsigned char tempRX, tempRX2;
unsigned int broj1,broj2;
unsigned int adc_reg;

/***********************************************/
/*
 * Timer interrupt
 */
/***********************************************/

unsigned int timer_ms, delay_ms;
unsigned int timer_interrupt_us;
//unsigned int timer_us, delay_us;

void __attribute__((__interrupt__)) _T1Interrupt(void)
{
    /* cannot implement timer_us and delay_us - too costly */
   	TMR1 = 0;
    IFS0bits.T1IF = 0;
    timer_interrupt_us = 1;
}

void __attribute__((__interrupt__)) _T2Interrupt(void)
{
   	TMR2 = 0;
    IFS0bits.T2IF = 0;
}

void __attribute__((__interrupt__)) _T3Interrupt(void)
{
   	TMR3 = 0;
    IFS0bits.T3IF = 0;
}

void __attribute__((__interrupt__)) _T4Interrupt(void)
{
   	TMR4 = 0;
    if (++timer_ms == MAX_TIMER_VAL) timer_ms = 0;
    if (++delay_ms == MAX_TIMER_VAL) delay_ms = 0;
    IFS1bits.T4IF = 0;
}

void __attribute__((__interrupt__)) _T5Interrupt(void)
{
   	TMR5 = 0;
    IFS1bits.T5IF = 0;
}

/***********************************************/
/*
 * UART interrupt
 */
/***********************************************/

void __attribute__((__interrupt__)) _U1RXInterrupt(void)  // to Bluetooth
{
    IFS0bits.U1RXIF = 0;
    tempRX=U1RXREG;

}

void __attribute__((__interrupt__)) _U2RXInterrupt(void) { // to PC 
    IFS1bits.U2RXIF = 0;
    tempRX2 = U2RXREG;
}

/***********************************************/
/*
 * ADC interrupt
 */
/***********************************************/

void __attribute__((__interrupt__)) _ADCInterrupt(void) {
    adc_reg=ADCBUF0;
    IFS0bits.ADIF = 0;
} 

/***********************************************/
/*
 * MAIN
 */
/***********************************************/

int main(void){
	for(broj1=0;broj1<10000;broj1++);
    initUART1();
    initUART2();
    WriteUART1_string("start ");
    
    ADCinit();
    init_motor();
    mot1_init_pwm();
    mot2_init_pwm();
    mot1_set_pwm(0);
    mot2_set_pwm(0);
    set_stop();
    
    Init_T4();
    Init_T1();
    init_forward_sensor();
    init_left_sensor();

    unsigned int forward_distance_mm = 0;
    unsigned int left_distance_mm = 0;
    int i = 0;
        
	while(1)
	{
        forward_distance_mm = 0;
        left_distance_mm = 0;
        for (i=0;i<TIMES_MEASURED;++i){
            forward_distance_mm += IR_read();//get_forward_mm();
            left_distance_mm += get_left_mm();
        }
        forward_distance_mm /= TIMES_MEASURED;
        left_distance_mm /= TIMES_MEASURED;
        
        WriteUART1_string("LEVO:");
        WriteUART1_int(left_distance_mm);
        WriteUART1_string("mm. ");
        WriteUART1_string("DALJ:");
        WriteUART1_int(forward_distance_mm);
        WriteUART1_string("mm. ");
        Delay_ms(1000);

        /*******************************************/       
        // object ahead. go back
        if (forward_distance_mm > SENSOR_ERROR && forward_distance_mm <= 150) {
            WriteUART1_string("back. ");
            set_left();
            set_backward();
            //Delay_ms(500);
            
            //set_stop_left_right();
            //set_forward();
            //Delay_ms(100);
        }
        // nothing deteted. go left
        else if (further_than(400,forward_distance_mm) && further_than(300,left_distance_mm)) {
            WriteUART1_string("left. ");
            set_left();
            set_forward();
            //Delay_ms(400);
            
            //set_stop_left_right();
            //set_backward();
            //Delay_ms(100);
        }
        // perfectly aligned. go forward
        else if (further_than(400,forward_distance_mm) && left_distance_mm > 150 && left_distance_mm <= 300) {
            WriteUART1_string("forward. ");
            set_stop_left_right();
            set_forward();
            //Delay_ms(400);   
            
            //set_backward();
            //Delay_ms(100);
        }

        // go right
        else if ((forward_distance_mm < 400) || (left_distance_mm > SENSOR_ERROR && left_distance_mm <= 150)) {
            WriteUART1_string("right. ");
            set_forward();
            set_right();
            //Delay_ms(400);
            
            //set_stop_left_right();
            //set_backward();
            //Delay_ms(100);
        }
        
        //set_stop();
        WriteUART1_char(tempRX);
        //Delay_ms(300);

    } // while
    return 0;
} // main
/*
 
        }   */ 