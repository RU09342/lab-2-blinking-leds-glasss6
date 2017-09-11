#include <msp430.h>


/**
 * blink.c
 */

unsigned int enabled = 0;

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;		// stop watchdog timer
	P1DIR |= (BIT0 + BIT6);			// configure P1.0 and P1.6 as output
	P1OUT &= ~(BIT0 + BIT6);		// reset the LEDs
	P1REN |= BIT3;					// puller-resistor on the button pin P1.3
	P1OUT |= BIT3;					// writes "1" to portpin, telling the resistor to pullup
	P1IES |= BIT3;					// triggers when you press the button, "~BIT3" for when release
	P1IE |= BIT3;					// enables selector-mask for generating interrupts on the pin

	__enable_interrupt(); 			// enable interrupts

	volatile unsigned int i;		// volatile to prevent optimization

	while(1)
	{
		if(enabled > 0)
		{
			P1OUT ^= (BIT0 + BIT6);		// toggle P1.0 and P1.6
			for(i=50000; i>0; i--);     // delay
		}
	}
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
	enabled ^= 0x01;
	P1IFG &= ~BIT3; // P1.3 (button) IFG cleared
	P1OUT &= ~(BIT0 + BIT6); // Clear the LEDs so they start in OFF state
}
