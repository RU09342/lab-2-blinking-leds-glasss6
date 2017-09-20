# Simple Blink
## Stephen Glass

## Compatibility
* MSP430G2553
* MSP430F5529
* MSP430FR2311
* MSP430FR5994
* MSP430FR6989

## Description
The Simple Blink directory contains code to blink an LED with a 50% duty cycle on multiple TI MSP430XX LaunchPad development boards.
In each source file, we define the correct LED pins as an output. However. in this simple case, all boards use P1.0 as an LED output. While in an infinite loop, we perform a bitwise exclusive OR (XOR) on the LED output to toggle output on/off. A software delay is performed after the toggle. When the delay is completed, the infinite loop will resume toggling LEDs output and delaying.