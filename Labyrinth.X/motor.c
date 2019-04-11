#include "motor.h"

/***********************************************/
/*
 * PWM
 */
/***********************************************/

void mot1_init_pwm(void)
{
    PR2=2499;
    OC1RS=20;
    OC1R=1000;
    OC1CON = OCxCON_OCSIDL_CONTINUE 
            | OCxCON_OCTSEL_TIMER2 
            | OCxCON_OCM_PWM_ON_FAULT_DISABLED;
    T2CONbits.TON=1;
    OC1RS=1249;
}

void mot2_init_pwm(){
    PR3=2499;
    OC2RS=20;
    OC2R=1000;
    OC2CON = OCxCON_OCSIDL_CONTINUE 
            | OCxCON_OCTSEL_TIMER3 
            | OCxCON_OCM_PWM_ON_FAULT_DISABLED;
    T3CONbits.TON=1;
    OC2RS=1249;
}

void mot1_set_pwm(int duty)
{
    OC1RS = duty;
}

void mot2_set_pwm(int duty)
{
    OC2RS = duty;
}

void mot_set_pwm(int duty)
{
    mot1_set_pwm(duty);
    mot2_set_pwm(duty);
    
}

/***********************************************/
/*
 * MOVEMENT
 */
/***********************************************/

void init_motor()
{
    MOT_IN1_ADPCFG = 1;
    MOT_IN2_ADPCFG = 1;
    
    MOT_EN1_TRIS = 0;
    MOT_EN2_TRIS = 0;
    MOT_IN1_TRIS = 0;
    MOT_IN2_TRIS = 0;
    MOT_IN3_TRIS = 0;
    MOT_IN4_TRIS = 0;
}

void set_turbo()
{
    if (MOT_IN3_LAT == 0 || MOT_IN4_LAT == 1) {
        mot2_set_pwm(PWM_MIN);
        MOT_IN3_LAT = 1;
        MOT_IN4_LAT = 0;
        mot2_set_pwm(PWM_MAX);
    }
}

void set_left()
{
    if (!(MOT_IN1_LAT == 1 && MOT_IN2_LAT == 0 && MOT_IN3_LAT == 1 && MOT_IN4_LAT == 0)) {
        mot1_set_pwm(PWM_MIN);
        MOT_IN1_LAT = 1;
        MOT_IN2_LAT = 0;
        mot1_set_pwm(PWM_MID);
        
        mot2_set_pwm(PWM_MIN);
        MOT_IN3_LAT = 1;
        MOT_IN4_LAT = 0;
        mot2_set_pwm(PWM_MID);
    }
}

void set_right()
{
    if (!(MOT_IN1_LAT == 0 && MOT_IN2_LAT == 1 && MOT_IN3_LAT == 0 && MOT_IN4_LAT == 1)) {
        mot1_set_pwm(PWM_MIN);
        MOT_IN1_LAT = 0;
        MOT_IN2_LAT = 1;
        mot1_set_pwm(PWM_MID);
        
        mot2_set_pwm(PWM_MIN);
        MOT_IN3_LAT = 0;
        MOT_IN4_LAT = 1;
        mot2_set_pwm(PWM_MID);
    }
}

void set_backward()
{
    if (!(MOT_IN1_LAT == 1 && MOT_IN2_LAT == 0 && MOT_IN3_LAT == 0 && MOT_IN4_LAT == 1)) {
        mot1_set_pwm(PWM_MIN);
        MOT_IN1_LAT = 1;
        MOT_IN2_LAT = 0;
        mot1_set_pwm(PWM_MID);
        
        mot2_set_pwm(PWM_MIN);
        MOT_IN3_LAT = 0;
        MOT_IN4_LAT = 1;
        mot2_set_pwm(PWM_MID);
    }
}

void set_forward()
{
    if (!(MOT_IN1_LAT == 0 && MOT_IN2_LAT == 1 && MOT_IN3_LAT == 1 && MOT_IN4_LAT == 0)) {
        mot1_set_pwm(PWM_MIN);
        MOT_IN1_LAT = 0;
        MOT_IN2_LAT = 1;
        mot1_set_pwm(PWM_MID);
        
        mot2_set_pwm(PWM_MIN);
        MOT_IN3_LAT = 1;
        MOT_IN4_LAT = 0;
        mot2_set_pwm(PWM_MID);
    }
}

void set_stop()
{
    mot1_set_pwm(PWM_MIN);
    mot2_set_pwm(PWM_MIN);
    MOT_IN1_LAT = 0;
    MOT_IN2_LAT = 0;
    MOT_IN3_LAT = 0;
    MOT_IN4_LAT = 0;
}
