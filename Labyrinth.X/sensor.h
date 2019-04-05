/* 
 * File:   sensor.h
 * Author: Vladimir Vincan EE5-2015
 *
 * Created on April 2, 2019, 3:19 AM
 */

#ifndef SENSOR_H
#define	SENSOR_H

#ifdef	__cplusplus
extern "C" {
#endif

#include<p30fxxxx.h>
#include "timer.h" 
#include "uart.h"
    
/*#define SENSOR_FORWARD_TRIG_ADPCFG ADPCFGbits.PCFG0
#define SENSOR_FORWARD_ECHO_ADPCFG ADPCFGbits.PCFG1
#define SENSOR_LEFT_TRIG_ADPCFG ADPCFGbits.PCFG2    
#define SENSOR_LEFT_ECHO_ADPCFG ADPCFGbits.PCFG3
    
#define SENSOR_FORWARD_TRIG_TRIS TRISBbits.TRISB0 
#define SENSOR_FORWARD_ECHO_TRIS TRISBbits.TRISB1
#define SENSOR_LEFT_TRIG_TRIS TRISBbits.TRISB2
#define SENSOR_LEFT_ECHO_TRIS TRISBbits.TRISB3   
    
#define SENSOR_FORWARD_TRIG_LAT LATBbits.LATB0 
#define SENSOR_FORWARD_ECHO_PORT PORTBbits.RB1
#define SENSOR_LEFT_TRIG_LAT LATBbits.LATB2
#define SENSOR_LEFT_ECHO_PORT PORTBbits.RB3 */   
    
#define SENSOR_FORWARD_TRIG_TRIS TRISCbits.TRISC13 
#define SENSOR_FORWARD_ECHO_TRIS TRISCbits.TRISC14
#define SENSOR_LEFT_TRIG_TRIS TRISDbits.TRISD9
#define SENSOR_LEFT_ECHO_TRIS TRISDbits.TRISD3   
    
#define SENSOR_FORWARD_TRIG_LAT LATCbits.LATC13 
#define SENSOR_FORWARD_ECHO_PORT PORTCbits.RC14
#define SENSOR_LEFT_TRIG_LAT LATDbits.LATD9
#define SENSOR_LEFT_ECHO_PORT PORTDbits.RD3
    
#define MAX_LOW_TIME 1500
#define MAX_HIGH_TIME 1500
#define SENSOR_ERROR 35
    
void init_forward_sensor(void);
void init_left_sensor(void);

unsigned int get_forward_mm(void);
unsigned int get_left_mm(void);
unsigned int further_than(unsigned int compare_mm, unsigned int measured_mm);

#ifdef	__cplusplus
}
#endif

#endif	/* SENSOR_H */

