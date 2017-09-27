#include <msp430.h>


/**
 * blink.c
 Blink an LED with ~250000uS delay.
 This code is designed to be used as an off-board application with the MSP430G2553.
 MSP430G2553
 Stephen Glass
 */

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;		// stop watchdog timer
	P1DIR |= 0x01;					// configure P1.0 as output

	while(1)
	{
		P1OUT ^= 0x01;				// toggle P1.0 LED
		__delay_cylces(250000);
	}
}
