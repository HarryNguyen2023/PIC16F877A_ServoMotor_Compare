#include <xc.h>
#include "config.h"
#include "XC8_Servo_Compare.h"
#include "UART.h"
#include "XC8_ADC.h"
#include <stdio.h>

// Define command to control the position of Servo motor
#define Angle0 48
#define Angle30 49
#define Angle45 50
#define Angle90 51
#define Angle120 52
#define Angle150 53
#define Angle180 54
#define Mode 97

// Variables
char rcvStr[17];
uint8_t command;
uint8_t mode = 0;

// Function to control the position of the servo motor according to UART command
void UART_Pos(uint8_t com)
{
    if(com == Angle0){
        ServoAngle(0);
    }else if(com == Angle30){
        ServoAngle(30);
    }else if(com == Angle45){
        ServoAngle(45);
    }else if(com == Angle90){
        ServoAngle(90);
    }else if(com == Angle120){
        ServoAngle(120);
    }else if(com == Angle150){
        ServoAngle(150);
    }else if(com == Angle180){
        ServoAngle(180);
    }else{
        UART_sendString("Invalid input!\r\n");
        return;
    }
    UART_sendString("Completed!\r\n");
}

// Function to control the position of the servo motor using potentiometer
void PosControl_Pot(void)
{
    // Declare variable
    unsigned int adc = 0;
    uint8_t adc_angle = 0;
    // Read the potentiometer value
    adc = ADC_Read(0);
    // Rescale the angle value
    float adc_val = (adc / 1023.0f) * 180;
    adc_angle = (uint8_t)adc_val;
    ServoAngle(adc_angle);
    __delay_ms(1000);
}

// Interrupt
void __interrupt() ISR(void){
    // Timer 1 interrupt 
    if(TMR1IF)
    {
        TMR1 = TIME1;
        CCP1CON = 0x00;
        PWM = 1;
        CCP1CON = 0x09;
        // Clear the flag bit
        TMR1IF = 0;
    }
    // UART interrupt
    if(RCIF){
        // Error handling
        if (OERR) 
        {
            CREN = 0; 
            CREN = 1;  
        }
        command = RCREG;
        sprintf(rcvStr, "Received: %c\r\n", command);
        UART_sendString(rcvStr);
        if(command == Mode)
        {
            mode = 0;
        }
        else
        {
            mode = 1;
            UART_Pos(command);
        } 
    }
}

void main(void) {
    // Initiate system
    UART_Init();
    ADC_Init();
    Servo_Init();
    __delay_ms(50);
    UART_sendString("System is ready\r\n");
    // Main duty
    while(1)
    {      
        if(mode == 0){
            PosControl_Pot();
        }
    } 
    return;
}
