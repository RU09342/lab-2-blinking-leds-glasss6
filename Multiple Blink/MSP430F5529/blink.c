#include <msp430.h>


/*
 * blink.c
   Blinks two LEDs at a 50% duty cycle
   MSP430F5529
   Stephen Glass
*/

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer
    P1DIR |= (BIT0);                // configure P1.0 as output
    P4DIR |= (BIT7);                // configure P4.7 as output
    P1OUT = 1;                      // P1.0 starts ON
    P4OUT = 0;                      // P4.7 starts OFF
    // LED P1.0 will be on when P4.7 is off

    while(1)
    {
        P1OUT ^= (BIT0);            // toggle P1.0
        P4OUT ^= (BIT7);            // toggle P4.7
        __delay_cycles(250000);     // a ~250000uS pause
    }
}
