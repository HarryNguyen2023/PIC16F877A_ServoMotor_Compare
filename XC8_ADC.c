#include "XC8_ADC.h"
#include "UART.h"

// Function to configure ADC module
void ADC_Init()
{
    ADCON0 = 0b01000001;
    ADCON1 = 0x80;
}

// Function to read ADC value from potentiometer
unsigned int ADC_Read(uint8_t ANC){
    // Valid the channel name
    if((ANC < 0) || (ANC > 7)){
        return 0;
    }
    // Clear the channel selection bit
    ADCON0 &= 0b11000101;
    // Select the desired channel
    ADCON0 |= ANC<<3;
    // Wait for the acquisition time 
    __delay_us(30);
    // Start the ADC read
    GO_DONE = 1;
    // Waiting for the conversion to be completed
    while(ADCON0bits.GO_DONE);
    return ((ADRESH << 8) + ADRESL);
}