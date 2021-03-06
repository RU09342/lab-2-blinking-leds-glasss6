#include <msp430.h>


/**
 * blink.c
 Start blinking two LEDs with 50% duty cycle when button is pressed.
 This version uses interrupts. See blink_polling.c for use with polling method.
 MSP430G2553
 Stephen Glass
 */

unsigned int enabled = 0;			// declare int to keep track of when the button was pressed

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;		// stop watchdog timer
	P1DIR |= (BIT0 + BIT6);			// configure P1.0 and P1.6 as output
	P1OUT &= ~(BIT0 + BIT6);		// reset the LEDs (both start off)

	P1REN |= BIT3;					// puller-resistor on the button pin P1.3
	P1OUT |= BIT3;					// writes "1" to P1.3, telling the resistor to pullup
	P1IES |= BIT3;					// telling it to trigger when you press the button P1.3, "~BIT3" for when release
	P1IE |= BIT3;					// enables selector-mask on P1.3 for generating interrupts on the pin

	__enable_interrupt(); 			// enable interrupts

	while(1)
	{
		if(enabled > 0) 			// if the button was pressed (enabled)
		{
			P1OUT ^= (BIT0 + BIT6);		// toggle P1.0 and P1.6 LEDs
			__delay_cycles(250000);     // a ~250000uS delay
		}
	}
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void) // function called when the port is interrupted (button pressed)
{
	enabled ^= 0x01; // toggle the enabled int on/off
	P1IFG &= ~BIT3; // P1.3 (button) IFG cleared
	P1OUT &= ~(BIT0 + BIT6); // Clear the LEDs so they start in OFF state
}