# Multiple Blink
## Stephen Glass

## Compatibility
* MSP430G2553
* MSP430F5529
* MSP430FR2311
* MSP430FR5994
* MSP430FR6989

## Description
The Simple Blink directory contains code to blink two on-board LEDs with a 50% duty cycle on multiple TI MSP430XX LaunchPad development boards. In each source file, we define the correct LEDs pins as an output. 

It is known from the Simple Blink source that all LaunchPads utilize P1.0 as a LED. However, the pin for the second LED varies between each board. E.g: LED2 on the MSP430G2553: P1.6, LED2 on the MSP430FR2311: P2.0. For each source file, we define the correct pins corresponding to the LaunchPad development.

While in an infinite loop, we perform a bitwise exclusive OR (XOR) on both LED outputs to toggle output on/off. A software delay is performed after the toggle (~250000uS delay). When the delay is completed, the infinite loop will resume toggling LEDs output and delaying.