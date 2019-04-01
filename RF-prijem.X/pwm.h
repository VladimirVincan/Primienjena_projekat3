/* 
 * File:   pwm.h
 * Author: Z1
 *
 * Created on March 3, 2019, 10:18 PM
 */

#ifndef PWM_H
#define	PWM_H

#ifdef	__cplusplus
extern "C" {
#endif

#define MOT_EN1_TRIS TRISDbits.TRISD0 
#define MOT_EN2_TRIS TRISDbits.TRISD1
#define MOT_IN1_TRIS TRISBbits.TRISB11
#define MOT_IN2_TRIS TRISBbits.TRISB12
#define MOT_IN3_TRIS TRISFbits.TRISF0
#define MOT_IN4_TRIS TRISFbits.TRISF1
    
#define MOT_IN1_LAT LATBbits.LATB11
#define MOT_IN2_LAT LATBbits.LATB12
#define MOT_IN3_LAT LATFbits.LATF0
#define MOT_IN4_LAT LATFbits.LATF1

#define OCxCON_OCSIDL_HALT 0x2000
#define OCxCON_OCSIDL_CONTINUE 0x0000 
#define OCxCON_OCTSEL_TIMER3 0x0008
#define OCxCON_OCTSEL_TIMER2 0x0000
#define OCxCON_OCM_PWM_ON_FAULT_ENABLED 0x0007 
#define OCxCON_OCM_PWM_ON_FAULT_DISABLED 0x0006
    
#define PWM_MIN 0
#define PWM_MID 1249    
#define PWM_MAX 2499

#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H */

