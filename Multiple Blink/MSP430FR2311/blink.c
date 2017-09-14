#include <msp430.h>


/**
 * blink.c
 */
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer
    P1DIR |= (BIT0);                // configure P1.0 as output
    P2DIR |= (BIT0);
    P1OUT = 1; // P1.0 starts ON
    P2OUT = 0;

    volatile unsigned int i;        // volatile to prevent optimization

    while(1)
    {
        P1OUT ^= (BIT0);        // toggle P1.0
        P2OUT ^= (BIT0);
        __delay_cycles(250000); // a ~250000uS pause
    }
}
