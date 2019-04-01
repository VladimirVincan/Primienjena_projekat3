/* 
 * File:   movement.h
 * Author: Z1
 *
 * Created on March 4, 2019, 1:15 AM
 */

#ifndef MOVEMENT_H
#define	MOVEMENT_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "pwm.h"
#include<p30fxxxx.h>
    
void init_pins();
void set_forward();
void set_backward();
void set_left();
void set_right();

#ifdef	__cplusplus
}
#endif

#endif	/* MOVEMENT_H */

