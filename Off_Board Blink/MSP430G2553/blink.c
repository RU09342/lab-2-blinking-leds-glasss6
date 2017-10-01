#include <msp430.h>


/**
 * blink.c
 Blink two LEDs vc with ~250000uS delay.
 This code is designed to be used as an off-board application with the MSP430G2553.
 MSP430G2553
 Stephen Glass
 */

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;		// stop watchdog timer
	P1DIR |= (BIT0 + BIT6);			// configure P1.0 and P1.6 as output
	P1OUT &= ~(BIT0 + BIT6); 		// reset the LEDs so they start in off position

	while(1)
	{
		P1OUT ^= (BIT0 + BIT6);				// toggle P1.0 and P1.6LED
		__delay_cylces(250000);
	}
}
