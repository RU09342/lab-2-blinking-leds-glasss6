#include <msp430.h>


/**
 * blink.c
 Simple 50% duty cycle LED blink
 MSP430G2553
 Stephen Glass
 */

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;		// stop watchdog timer
	P1DIR |= 0x01;					// configure P1.0 as output

	while(1)						// never ending loop
	{
		P1OUT ^= 0x01;				// toggle P1.0 LED
		__delay_cycles(250000);     // a ~250000uS delay
	}
}
