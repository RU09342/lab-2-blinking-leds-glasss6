#include <msp430.h>


/**
 * blink.c
 */
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;		// stop watchdog timer
	P1DIR |= (BIT0 + BIT6);			// configure P1.0 and P1.6 as output
	P1OUT &= ~(BIT0 + BIT6);		// reset the LEDs

	volatile unsigned int i;		// volatile to prevent optimization

	while(1)
	{
		P1OUT ^= (BIT0 + BIT6);		// toggle P1.0 and P1.6
		for(i=50000; i>0; i--);     // delay
	}
}
