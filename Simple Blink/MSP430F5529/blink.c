#include <msp430.h>				

/**
 * blink.c
 Simple 50% duty cycle LED blink
 MSP430F5529
 Stephen Glass
 */

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;		// stop watchdog timer
	P1DIR |= 0x01;					// configure P1.0 LED as output

	while(1)
	{
		P1OUT ^= 0x01;				// toggle P1.0 LED
		__delay_cycles(250000);     // a ~250000uS delay
	}
}
