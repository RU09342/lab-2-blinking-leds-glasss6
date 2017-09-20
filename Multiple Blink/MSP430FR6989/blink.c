/*
 * blink.c
   Blinks two LEDs at a 50% duty cycle
   MSP430FR6989
   Stephen Glass
*/

#include <msp430.h>

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings
    P1DIR |= 0x01;                          // Set P1.0 to output direction
    P9DIR |= BIT7;                          // Set P9.7 to output

    for(;;) {

        P1OUT ^= 0x01;                      // Toggle P1.0 LED using exclusive-OR
        P9OUT ^= BIT7;                      // Toggle P9.7 LED using XOR

        __delay_cycles(250000);             // a ~250000uS delay
    }
}
