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
    
#define SENSOR_FORWARD_TRIG_ADPCFG ADPCFGbits.PCFG0
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
#define SENSOR_LEFT_ECHO_PORT PORTBbits.RB3    
    
#define MAX_LOW_TIME 1500
#define MAX_HIGH_TIME 1500
    
void init_forward_sensor(void);
void init_left_sensor(void);

int get_forward_cm(void);
int get_left_cm(void);

#ifdef	__cplusplus
}
#endif

#endif	/* SENSOR_H */

