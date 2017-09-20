#include <msp430.h>


/*
 * blink.c
   Blinks two LEDs at a 50% duty cycle
   MSP430FR2311
   Stephen Glass
*/

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer
    P1DIR |= (BIT0);                // configure P1.0 as output
    P2DIR |= (BIT0);                // configure P2.0 as output
    P1OUT = 1;                      // P1.0 starts ON
    P2OUT = 0;                      // P2.0 starts OFF 
    // P1.0 will be on when P2.0 is off

    volatile unsigned int i;        // create int for SW Delay

    while(1)
    {
        P1OUT ^= (BIT0);            // toggle P1.0
        P2OUT ^= (BIT0);            // toggle P2.0
        __delay_cycles(250000);     // a ~250000uS delay
    }
}
