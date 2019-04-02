#include <p30fxxxx.h>
#include <p30f4013.h>
#include "motor.h"
#include "uart.h"
#include "sensor.h"
#include "timer.h"

_FOSC(CSW_FSCM_OFF & XT_PLL4);
_FWDT(WDT_OFF);

#define MAX_TIMER_VAL 32000

unsigned char tempRX, tempRX2;
unsigned int broj1,broj2;

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
 * MAIN
 */
/***********************************************/

int main(void){
	for(broj1=0;broj1<10000;broj1++);
    initUART1();
    initUART2();
    WriteUART1_string("start ");
    
    init_motor();
    mot1_init_pwm();
    mot2_init_pwm();
    mot1_set_pwm(0);
    mot2_set_pwm(0);
    set_stop();
    
    Init_T4();
    WriteUART1_string("Prosao T4 ");
    Init_T1();
    init_forward_sensor();
    init_left_sensor();

	while(1)
	{
        WriteUART1_string("Razdaljina: ");
        WriteUART1_int(get_forward_cm());
        WriteUART1_string("cm");
        WriteUART1_char(tempRX);
        Delay_ms(1000);
       /* WriteUART1_string("Serijska v2");
        WriteUART1_char(tempRX);
        if (i<4){
            set_left();
            set_forward();
            i++;
        }
        else if (i<10){
            set_stop();
            i++;
        }
        else if (i<14) {
            set_right();
            set_backward();
            i++;
        }
        else {
            set_stop();
            if (i>=20) i = 0;
            i++;
        }
        
      
        for(broj2=0;broj2<1000;broj2++);*/
    } // while
    return 0;
} // main






