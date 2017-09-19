#include <msp430.h>


/**
 * blink.c
 */

unsigned int enabled = 0;

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;           // Disable the GPIO power-on default high-impedance mode (needed for FR5994)
    P1DIR |= (BIT0 + BIT1);         // configure P1.0 and P1.1 as output
    P1OUT &= ~(BIT0 + BIT1);        // reset the LEDs
    P5REN |= BIT6;                  // puller-resistor on the button pin P5.6
    P5OUT |= BIT6;                  // writes "1" to portpin, telling the resistor to pullup
    P5IES |= BIT6;                  // triggers when you press the button, "~BIT3" for when release
    P5IE |= BIT6;                   // enables selector-mask for generating interrupts on the pin

    __enable_interrupt();           // enable interrupts

    volatile unsigned int i;        // volatile to prevent optimization

    while(1)
    {
        if(enabled > 0)
        {
            P1OUT ^= (BIT0);            // toggle P1.0
            for(i=25000; i>0; i--);     // delay
        }
        else
        {
            P1OUT ^= (BIT1);            // toggle P1.16
            for(i=25000; i>0; i--);     // delay
        }
    }
}

// Port 1 interrupt service routine
#pragma vector=PORT5_VECTOR
__interrupt void Port_5(void)
{
    enabled ^= 0x01;
    P5IFG &= ~BIT3; // P5.6 (button) IFG cleared
    P1OUT &= ~(BIT0 + BIT1); // Clear the LEDs so they start in OFF state
}