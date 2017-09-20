#include <msp430.h>


/**
 * blink.c
 Switch between blinking two LEDs with 50% duty cycle when button is pressed.
 This is an extension of blink.c. This code will allow you switch between which LED is blinking by pressing a button.
 MSP430G2553
 Stephen Glass
 */

unsigned int enabled = 0;           // declare int to keep track of when the button was pressed
// By default P1.0 will flash. Pressing the button will flash other LED.

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer
    P1DIR |= (BIT0 + BIT6);         // configure P1.0 and P1.6 as output
    P1OUT &= ~(BIT0 + BIT6);        // reset the LEDs (both start off)

    P1REN |= BIT3;                  // puller-resistor on the button pin P1.3
    P1OUT |= BIT3;                  // writes "1" to P1.3, telling the resistor to pullup
    P1IES |= BIT3;                  // telling it to trigger when you press the button P1.3, "~BIT3" for when release
    P1IE |= BIT3;                   // enables selector-mask on P1.3 for generating interrupts on the pin

    __enable_interrupt();           // enable interrupts

    while(1)
    {
        if(enabled > 0)             // if the button was pressed and enable was set
        {
            P1OUT ^= (BIT6);            // toggle P1.6
            __delay_cycles(250000);     // a ~250000uS delay
        }
        else                        // if the button was pressed and enable was reset
        {
            P1OUT ^= (BIT0);            // toggle P1.0
            __delay_cycles(250000);     // a ~250000uS delay
        }
    }
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    enabled ^= 0x01; // toggle the enabled int on/off (this determines which LED is blinking)
    P1IFG &= ~BIT3; // P1.3 (button) IFG cleared
    P1OUT &= ~(BIT0 + BIT6); // Clear the LEDs so they start in OFF state
}
