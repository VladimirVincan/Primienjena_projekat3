#include "movement.h"
unsigned int broj1,broj2;

void init_pins()
{
    TRISDbits.TRISD0=0; // EN1
    TRISDbits.TRISD1=0; // EN2
    TRISDbits.TRISD2=0; // IN1
    TRISDbits.TRISD3=0; // IN2
    TRISDbits.TRISD8=0; // IN3
    TRISDbits.TRISD9=0; // IN4
}

void set_forward()
{
    LATDbits.LATD0 = 0; // EN1
    for(broj1=0;broj1<10000;broj1++);
    LATDbits.LATD2=1; // IN1
    LATDbits.LATD3=0; // IN2 
    LATDbits.LATD0 = 1; // EN1
}

void set_backward()
{
    LATDbits.LATD0 = 0; // EN1
    for(broj1=0;broj1<10000;broj1++);
    LATDbits.LATD2=0; // IN1
    LATDbits.LATD3=1; // IN2
    LATDbits.LATD0 = 1; // EN1
}

void set_left()
{
    LATDbits.LATD1 = 0; // EN2
    for(broj1=0;broj1<10000;broj1++);
    LATDbits.LATD8=1; // IN3
    LATDbits.LATD9=0; // IN4
    LATDbits.LATD1 = 1; // EN2
}

void set_right()
{
    LATDbits.LATD1 = 0; // EN2
    for(broj1=0;broj1<10000;broj1++);
    LATDbits.LATD8=0; // IN3
    LATDbits.LATD9=1; // IN4
    LATDbits.LATD1 = 1; // EN2
}
