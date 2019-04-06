#include "sensor.h"

void init_forward_sensor(void){
    //SENSOR_FORWARD_TRIG_ADPCFG = 1;
    //SENSOR_FORWARD_ECHO_ADPCFG = 1;
    
    SENSOR_FORWARD_TRIG_TRIS = 0;
    SENSOR_FORWARD_ECHO_TRIS = 1;
    
    SENSOR_FORWARD_TRIG_LAT = 0;
}

void init_left_sensor(void){
    //SENSOR_LEFT_TRIG_ADPCFG = 1;
    //SENSOR_LEFT_ECHO_ADPCFG = 1;
    
    SENSOR_LEFT_TRIG_TRIS = 0;
    SENSOR_LEFT_ECHO_TRIS = 1;
    
    SENSOR_LEFT_TRIG_LAT = 0;
}

unsigned int get_forward_mm(void){
    Delay_ms(100);
    SENSOR_FORWARD_TRIG_LAT = 1;
    Delay_us(20);
    SENSOR_FORWARD_TRIG_LAT = 0;
    
    while (SENSOR_FORWARD_ECHO_PORT == 0); //TODO: && read_timer_us() <= MAX_LOW_TIME);
    start_measuring_time_us();
    while (SENSOR_FORWARD_ECHO_PORT == 1); //TODO: && read_timer_us() <= MAX_HIGH_TIME);
    
    return return_time_measurement_us() / 9.11;
}

unsigned int get_left_mm(void){
    Delay_ms(100);
    SENSOR_LEFT_TRIG_LAT = 1;
    Delay_us(20);
    SENSOR_LEFT_TRIG_LAT = 0;
    
    while (SENSOR_LEFT_ECHO_PORT == 0); //TODO: && read_timer_us() <= MAX_LOW_TIME);
    start_measuring_time_us();
    while (SENSOR_LEFT_ECHO_PORT == 1); //TODO: && read_timer_us() <= MAX_HIGH_TIME);
    
    return return_time_measurement_us() / 9.11;//58;
}

unsigned int further_than(unsigned int compare_mm, unsigned int measured_mm){
    return measured_mm < SENSOR_ERROR || measured_mm > compare_mm;
}