#include <msp430.h>


/**
 * blink.c
 Switch between blinking two LEDs with 50% duty cycle when button is pressed.
 This is an extension of blink.c. This code will allow you switch between which LED is blinking by pressing a button.
 MSP430FR6989
 Stephen Glass
 */

unsigned int enabled = 0; // declare int to keep track of when the button was pressed
// By default P1.0 will flash. Pressing the button will flash other LED.

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer
    P1DIR |= (BIT0);                // configure P1.0 as output
    P9DIR |= (BIT7);                // configure P9.7 as output

    P1OUT &= ~(BIT0);               // reset the LEDs (p1.0)
    P9OUT &= ~(BIT7);               // reset the LEDs (p9.7)


    P1REN |= BIT1;                  // puller-resistor on the button pin P1.1
    P1OUT |= BIT1;                  // writes "1" to portpin, telling the resistor to pullup
    P1IES |= BIT1;                  // triggers when you press the button, "~BIT3" for when release
    P1IE |= BIT1;                   // enables selector-mask for generating interrupts on the pin

    __enable_interrupt();           // enable interrupts

    while(1)
    {
        if(enabled > 0) // if the button was pressed and enable was set
        {
            P1OUT ^= (BIT0);            // toggle P1.0
            __delay_cycles(250000);     // a ~250000uS delay
        }
        else
        {
            P9OUT ^= (BIT7);            // toggle P9.7
            __delay_cycles(250000);     // a ~250000uS delay
        }
    }
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    enabled ^= 0x01; // toggle the enabled int on/off (this determines which LED is blinking)
    P1IFG &= ~BIT1; // P1.1 (button) IFG cleared
    P1OUT &= ~(BIT0); // Clear the LEDs so they start in OFF state
    P9OUT &= ~(BIT7); // Clear the LEDs so they start in OFF state
}
