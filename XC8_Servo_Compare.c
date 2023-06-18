#include "XC8_Servo_Compare.h"

// Function to configure TIMER1 module
void Timer1_Init()
{
    // Reset value of Timer1
    TMR1 = TIME1;
    // Set pre-scaler to 1:8
    T1CKPS1 = 1;
    T1CKPS0 = 1;
    // Timer Mode
    TMR1CS = 0;
    TMR1ON = 1;
    // Enable timer 1 interrupt
    TMR1IF = 0;
    TMR1IE = 1;
    PEIE = 1;
    GIE = 1;
}

// Function to configure Capture Mode
void Compare_Init()
{
    // Set Compare mode to reset Timer1
    CCP1M3 = 1;
    CCP1M2 = 0;
    CCP1M1 = 0;
    CCP1M0 = 1;
    // Set the desired compare value
    CCPR1 = TIME1 + (DC_RANGE / 20);
}

// Function to initiate servo motor
void Servo_Init()
{
    // Configure I/O pins
    TRISPWM = 0;
    PWM = 1;
    Timer1_Init();
    Compare_Init();
}

// Function to drive the servo motor to desired angle position
void ServoAngle(uint8_t angle)
{
    if(angle <= 180)
    {
        uint16_t dc = (uint16_t)((100 * angle) / 36.0) + TIME1 + (DC_RANGE / 20);
        CCPR1 = dc;
    }
}
