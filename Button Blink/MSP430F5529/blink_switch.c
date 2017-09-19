#include <msp430.h>


/**
 * blink.c
 */

unsigned int enabled = 0;

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer
    P1DIR |= (BIT0);                // configure P1.0 as output
    P4DIR |= (BIT7);                // configure P4.7 as output
    P1OUT &= ~(BIT0);               // reset the LEDs
    P4OUT &= ~(BIT7);

    P1REN |= BIT1;                  // puller-resistor on the button pin P1.1
    P1OUT |= BIT1;                  // writes "1" to portpin, telling the resistor to pullup
    P1IES |= BIT1;                  // triggers when you press the button, "~BIT1" for when release
    P1IE |= BIT1;                   // enables selector-mask for generating interrupts on the pin

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
            P4OUT ^= (BIT7);            // toggle P4.7
            for(i=25000; i>0; i--);     // delay
        }
    }
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    enabled ^= 0x01;
    P1IFG &= ~BIT1; // P1.1 (button) IFG cleared
    P1OUT &= ~(BIT0); // Clear the LEDs so they start in OFF state
    P4OUT &= ~(BIT7);
}
