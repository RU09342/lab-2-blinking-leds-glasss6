/*
 * blink.c
   Blinks two LEDs at a 50% duty cycle
   MSP430FR5994
   Stephen Glass
*/

#include <msp430.h>

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings
    P1DIR |= (BIT0 + BIT1);                 // Set P1.0 and P1.1 to output direction

    for(;;) {

        P1OUT ^= (BIT0 + BIT1);             // Toggle P1.0 and P1.1 using exclusive-OR

        __delay_cycles(250000);             // a ~250000uS delay
    }
}
