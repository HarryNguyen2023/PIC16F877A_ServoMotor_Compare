#include <xc.h>

// PWM pin
#define TRISPWM TRISC2
#define PWM RC2
uint16_t TIME1 = 55536;
uint16_t DC_RANGE = 10000;

// Function initialization
void Timer1_Init(void);
void Compare_Init(void);
void Servo_Init(void);
void ServoAngle(uint8_t angle);
