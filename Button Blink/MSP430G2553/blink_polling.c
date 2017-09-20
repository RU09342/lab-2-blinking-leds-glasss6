#include <msp430.h>

/**
 * blink.c
 Start blinking two LEDs with 50% duty cycle when button is pressed.
 This version uses POLLING. See blink.c for use with interrupts method.
 MSP430G2553
 Stephen Glass
 */

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD; // stop the watchdog timer

    P1DIR = (BIT6); // configure P1.6 as an output (LED)
    P1REN = (BIT3); // puller-resistor on the button pin P1.3
    P1OUT = (BIT2); // writes "1" to P1.3, telling the resistor to pullup

    while(1)
    {
        if((P1IN & BUTTON) == 0x00) // if the button is being pressed down
        {
            __delay_cycles(5000); // perform a software delay for ~5000uS
            if((P1IN & BUTTON) == 0x00) // if the button is still being pressed down
            // The statement above is used to minimize debouncing on the button by checking if its still being pressed (and not a false positive)
            {
                 P1OUT ^= (BIT6); // toggle the P1.6 LED on/off
                 while((P1IN & BUTTON) == 0x00); // wait for the status of the button to change (a.k.a be released) until continuing the code loop
            }
        }
    }
}