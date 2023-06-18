# PIC16F877A_ServoMotor_Compare
# Created 06/18/2023

This project is to prototype the ability to control the position of the MG 90 RC servo motor, using timer and compare module to approximate the PWM pulse with the typical frequency of 50Hz.

During this project, I have used the TIMER 1, as well as the CCP1 module of the PIC16F877A, to control the desired position through command by UART from my ocomputer. Because, I only control 1 servo motor, so I decided to connect it directly to the MCU. However, if more than one motor is used, we must use the motor driver instead.

![Servo motor circuit](https://github.com/HarryNguyen2023/PIC16F877A_ServoMotor_Compare/assets/136590151/a3d78980-945f-43a1-90a5-864af727f0a1)
