/* 
 * File:   adc.h
 * Author: Vladimir Vincan EE5-2015
 *
 * Created on April 5, 2019, 2:34 AM
 */

#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif

#include<p30fxxxx.h>

extern unsigned int adc_reg;    
    
//void ADCinit_analog(void);
void ADCinit(void);
unsigned int IR_read(void);


#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */



