#include "sensor.h"

void init_forward_sensor(void){
    SENSOR_FORWARD_TRIG_ADPCFG = 1;
    SENSOR_FORWARD_ECHO_ADPCFG = 1;
    
    SENSOR_FORWARD_TRIG_TRIS = 0;
    SENSOR_FORWARD_ECHO_TRIS = 1;
    
    SENSOR_FORWARD_TRIG_LAT = 0;
}
void init_left_sensor(void){
    SENSOR_LEFT_TRIG_ADPCFG = 1;
    SENSOR_LEFT_ECHO_ADPCFG = 1;
    
    SENSOR_LEFT_TRIG_TRIS = 0;
    SENSOR_LEFT_ECHO_TRIS = 1;
    
    SENSOR_LEFT_TRIG_LAT = 0;
}

int get_forward_cm(void){
    reset_timer_ms();
    Delay_ms(60);
    reset_timer_us();
    SENSOR_FORWARD_TRIG_LAT = 1;
    Delay_us(10);
    SENSOR_FORWARD_TRIG_LAT = 0;
    while (SENSOR_FORWARD_ECHO_PORT == 0 && read_timer_us() <= MAX_LOW_TIME);
    //WriteUART1_string(" time: ");
    //WriteUART1_int(read_timer_us());
    reset_timer_us();
    while (/*SENSOR_FORWARD_ECHO_PORT == 1 &&*/ read_timer_us() <= MAX_HIGH_TIME);
    WriteUART1_string(" time: ");
    WriteUART1_int(read_timer_us());
    WriteUART1_string(" ");
    return read_timer_us();// / 58;
}

int get_left_cm(void){
    reset_timer_ms();
    Delay_ms(60);
    reset_timer_us();
    SENSOR_LEFT_TRIG_LAT = 1;
    Delay_us(10);
    SENSOR_LEFT_TRIG_LAT = 0;
    while (SENSOR_LEFT_ECHO_PORT == 0 && read_timer_us() <= MAX_LOW_TIME);
    reset_timer_us();
    while (SENSOR_LEFT_ECHO_PORT == 1 && read_timer_us() <= MAX_HIGH_TIME);
    return read_timer_us() / 58;
}