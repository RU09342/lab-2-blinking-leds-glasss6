#include <msp430.h>

/**
 * blink.c
 Simple 50% duty cycle LED blink
 MSP430FR6989
 Stephen Glass
 */

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode (needed or no work)
    P1DIR |= 0x01;                          // Set P1.0 to output direction

    for(;;) {

        P1OUT ^= 0x01;                      // Toggle P1.0 LED using exclusive-OR

        __delay_cycles(250000);             // a ~250000uS delay
    }
}
