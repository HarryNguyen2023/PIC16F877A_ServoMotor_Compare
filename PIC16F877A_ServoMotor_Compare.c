#include "config.h"
#include "ServoMotor_compare.h"
#include "PIC16F877A_ADC.h"
#include "PIC16F877A_UART.h"
#include <stdio.h>

// Define command to control the position of servo motor
#define Angle0 48
#define Angle30 49
#define Angle45 50
#define Angle90 51
#define Angle120 52
#define Angle150 53
#define Angle180 54
#define ADC 97

// ADC channel to be used in this project
uint8_t adc_channels[1] = {0};

// Global variables
uint8_t mode = 0;

// Function prototypes
void positionControl(uint8_t com);
void adcPosControl(void);

// Interrupt
void __interrupt() ISR(void){
    // Timer 1 interrupt 
    if(TMR1IF)
    {
        // Change the status of the pulse to HIGH at timer 1 overflow
        servoShiftHigh();
        // Clear the flag bit
        TMR1IF = 0;
    }
    // UART interrupt
    if(RCIF){
        uint8_t command = UARTrcvChar();
        if(command == ADC)
            mode = 0;
        else
        {
            mode = 1;
            positionControl(command);
        } 
    }
}

void main(void) {
    // Initiate UART communication protocol for both transmission and reception
    UARTTransRcvInit();
    // Initiate the ADC channel to control the position of the motor vis potentionmeter
    ADC_Init(adc_channels, 1);
    // Initiate the servo motor
    servoInit();

    // Main duty
    while(1)
    {      
        if(mode == 0){
            adcPosControl();
            __delay_ms(250);
        }
    } 
    return;
}

// Function to control the position of the servo motor according to UART command
void positionControl(uint8_t com)
{
    if(com == Angle0)
        servoAngle(0);
    else if(com == Angle30)
        servoAngle(30);
    else if(com == Angle45)
        servoAngle(45);
    else if(com == Angle90)
        servoAngle(90);
    else if(com == Angle120)
        servoAngle(120);
    else if(com == Angle150)
        servoAngle(150);
    else if(com == Angle180)
        servoAngle(180);
    else
    {
        UARTsendString("Invalid input!\r\n");
        return;
    }
    UARTsendString("Completed!\r\n");
}

// Function to control the position of the servo motor using potentiometer
void adcPosControl()
{
    // Read the potentiometer value
    uint16_t pot_value = ADC_Read(0);
    // Rescale the angle value
    float adc_val = (pot_value / 1023.0f) * 180;
    uint8_t adc_angle = (uint8_t)adc_val;
    servoAngle(adc_angle);
}
