#include <p30fxxxx.h>
#include <p30f4013.h>
#include "motor.h"
#include "uart.h"
#include "sensor.h"
#include "timer.h"
//#include "ADC.h"

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
unsigned int timer_us;

#ifdef TIMER_H
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
    ++timer_us;
    IFS1bits.T5IF = 0;
}
#endif

/***********************************************/
/*
 * UART interrupt
 */
/***********************************************/

#ifdef UART_H
void __attribute__((__interrupt__)) _U1RXInterrupt(void)  // to Bluetooth
{
    IFS0bits.U1RXIF = 0;
    tempRX=U1RXREG;

}

void __attribute__((__interrupt__)) _U2RXInterrupt(void) { // to PC 
    IFS1bits.U2RXIF = 0;
    tempRX2 = U2RXREG;
}
#endif

/***********************************************/
/*
 * ADC interrupt
 */
/***********************************************/

#ifdef ADC_H
void __attribute__((__interrupt__)) _ADCInterrupt(void) {
    adc_reg=ADCBUF0;
    IFS0bits.ADIF = 0;
} 
#endif

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
    
#ifdef ADC_H
    ADCinit();
#endif
    init_motor();
    mot1_init_pwm();
    mot2_init_pwm();
    mot1_set_pwm(0);
    mot2_set_pwm(0);
    set_stop();
    
    Init_T1();
    Init_T4();
    Init_T5();
    init_forward_sensor();
    init_left_sensor();
    
    unsigned int forward_distance_mm = 0;
    unsigned int left_distance_mm = 0;
#ifdef ADC_H
    unsigned int forward_distance_ir = 0;
#endif

    unsigned int aligned = 1;
    int i = 0;
        
	while(1)
	{
        WriteUART1_char(10);
        WriteUART1_char(13);
     
        forward_distance_mm = 0;
        left_distance_mm = 0;
#ifdef ADC_H
        forward_distance_ir = 0;
#endif
        for (i=0;i<TIMES_MEASURED;++i){
            forward_distance_mm += get_forward_mm();//*10;
            left_distance_mm += get_left_mm();//*10;
#ifdef ADC_H
            forward_distance_ir += IR_read();
#endif
        }
        forward_distance_mm /= TIMES_MEASURED;
        left_distance_mm /= TIMES_MEASURED;
#ifdef ADC_H
        forward_distance_ir /= TIMES_MEASURED;
#endif
        
        WriteUART1_string("LEVO:");
        WriteUART1_int(left_distance_mm);
        WriteUART1_string("mm. ");
        WriteUART1_string("DALJ:");
        WriteUART1_int(forward_distance_mm);
        WriteUART1_string("mm. ");
#ifdef ADC_H
        WriteUART1_string("IR:");
        WriteUART1_int(forward_distance_mm);
        WriteUART1_string("cm. ");
#endif

        /*******************************************/     

#define TACTIC
#ifdef TACTIC
        // the sensor is at 45 deg from surface - doesn't read correctly
        if (left_distance_mm >= ROTATION_ERROR && !aligned) { 
            aligned = 1;
            int degree = 0, minv = left_distance_mm, curr = 0;
            WriteUART1_string("error. ");
            
            set_left();
            Delay_ms(ROT_TIME_30_DEGREE);
            set_stop();
            Delay_ms(STOP_TIME);
            curr = get_left_mm();
            if (curr < minv) {
                degree = -30;
                minv = curr;
            }
            
            set_left();
            Delay_ms(ROT_TIME_30_DEGREE); 
            set_stop();
            Delay_ms(STOP_TIME);
            curr = get_left_mm();
            if (curr < minv) {
                degree = -60;
                minv = curr;
            }
            
            set_right();
            Delay_ms(ROT_TIME_90_DEGREE);
            set_stop();
            Delay_ms(STOP_TIME);
            curr = get_left_mm();
            if (curr < minv) {
                degree = 30;
                minv = curr;
            }
            
            set_right();
            Delay_ms(ROT_TIME_30_DEGREE); 
            set_stop();
            Delay_ms(STOP_TIME);
            curr = get_left_mm();
            if (curr < minv) {
                degree = 60;
                minv = curr;
            }
            
            if (curr > RIGHT_CRIT)
                degree = 0;
            
            switch(degree){
                case 30:
                    set_left();
                    Delay_ms(ROT_TIME_30_DEGREE);
                    set_stop();
                    Delay_ms(STOP_TIME);
                    break;
                case 0:
                    set_left();
                    Delay_ms(ROT_TIME_30_DEGREE);
                    set_stop();
                    Delay_ms(STOP_TIME);
                    set_left();
                    Delay_ms(ROT_TIME_30_DEGREE);
                    set_stop();
                    Delay_ms(STOP_TIME);
                    break;
                case -30:
                    set_left();
                    Delay_ms(ROT_TIME_90_DEGREE);
                    set_stop();
                    Delay_ms(STOP_TIME);
                    break;
                case -60:
                    set_left();
                    Delay_ms(ROT_TIME_90_DEGREE);
                    set_stop();
                    Delay_ms(STOP_TIME);
                    set_left();
                    Delay_ms(ROT_TIME_30_DEGREE);
                    set_stop();
                    Delay_ms(STOP_TIME);
                    break;  
                case 60:
                default:
                    break;
            }
        }
        // object ahead. go back
        else if (forward_distance_mm <= FORWARD_CRIT) {
            aligned = 0;
            WriteUART1_string("back. ");
            set_backward();
            Delay_ms(BACKWARD_TIME);
            
            set_forward();
            Delay_ms(STOP_TIME);
        }
        // nothing detected. go left 90 degrees and continue forward
        else if (FORWARD_DIST < forward_distance_mm && RIGHT_CRIT < left_distance_mm) {
            aligned = 0;
            WriteUART1_string("left. ");
            set_left();
            Delay_ms(ROT_TIME_90_DEGREE);
            
            set_right();
            Delay_ms(STOP_TIME);
            
            set_forward();
            Delay_ms(FORWARD_TIME);
            
            set_backward();
            Delay_ms(STOP_TIME);
        }
        // perfectly aligned. go forward
        else if (FORWARD_DIST < forward_distance_mm && LEFT_DIST < left_distance_mm && left_distance_mm <= RIGHT_DIST) {
            aligned = 0;
            WriteUART1_string("forward. ");
            set_forward();
            Delay_ms(FORWARD_TIME);   
            
            set_backward();
            Delay_ms(STOP_TIME);
        }
        
        // go slight to the right
        else if (left_distance_mm <= LEFT_DIST) {
            aligned = 0;
            WriteUART1_string("slightRight. ");
            set_right();
            Delay_ms(ROT_TIME_30_DEGREE);
            
            set_left();
            Delay_ms(STOP_TIME);
            
            set_forward();
            Delay_ms(FORWARD_TIME);
            
            set_backward();
            Delay_ms(STOP_TIME);
        }
        // go slight to the left
        else if (RIGHT_DIST < left_distance_mm && left_distance_mm <= RIGHT_CRIT) {
            aligned = 0;
            WriteUART1_string("slightlEFT. ");
            set_left();
            Delay_ms(ROT_TIME_30_DEGREE);
            
            set_right();
            Delay_ms(STOP_TIME);
            
            set_forward();
            Delay_ms(FORWARD_TIME);
            
            set_backward();
            Delay_ms(STOP_TIME);
        }
        // go right 90 degrees
        else if (forward_distance_mm < RIGHT_DIST) {
            aligned = 0;
            WriteUART1_string("right. ");
            set_right();
            Delay_ms(ROT_TIME_90_DEGREE);
            
            set_left();
            Delay_ms(STOP_TIME);
        }
        
        set_stop();
        WriteUART1_char(tempRX);
        //Delay_ms(300);
#endif //TACTIC

    } // while
    return 0;
} // main
/*
 
        }   */ 