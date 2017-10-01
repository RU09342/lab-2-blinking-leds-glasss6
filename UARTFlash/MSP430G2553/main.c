#include <msp430.h>

/**
 * main.c
 UART Communication with the MSP430G2553 to control the flashing of two onboard LEDs
 MSP430G2553
 Stephen Glass
 */

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  if (CALBC1_1MHZ==0xFF)					          // If calibration constant erased
  {											
    while(1);                               // do not load, trap CPU!!	
  }
  DCOCTL = 0;                               // Select lowest DCOx and MODx settings
  BCSCTL1 = CALBC1_1MHZ;                    // Set DCO
  DCOCTL = CALDCO_1MHZ;
  P1SEL = BIT1 + BIT2 ;                     // P1.1 = RXD, P1.2=TXD
  P1SEL2 = BIT1 + BIT2 ;                    // P1.1 = RXD, P1.2=TXD
  UCA0CTL1 |= UCSSEL_2;                     // SMCLK
  UCA0BR0 = 104;                            // 1MHz 9600
  UCA0BR1 = 0;                              // 1MHz 9600
  UCA0MCTL = UCBRS0;                        // Modulation UCBRSx = 1
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX interrupt

  P1DIR |= (BIT0 + BIT6);

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0, interrupts enabled
}

//  Echo back RXed character, confirm TX buffer is ready first
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCIAB0RX_VECTOR))) USCI0RX_ISR (void)
#else
#error Compiler not supported!
#endif
{
  while (!(IFG2&UCA0TXIFG));                // USCI_A0 TX buffer ready?
  if(UCA0RXBUF == '1')                      // If we received the character '1'
  {
      P1OUT ^= (BIT0);                      // Toggle LED of P1.0
  }
  else if (UCA0RXBUF == '2') P1OUT ^= (BIT6); // If we received the character '2', toggle LED P1.6
  else if (UCA0RXBUF == '3') P1OUT ^= (BIT0 + BIT6); // If we received the character '3', toggle BOTH LED P1.0 and P1.6
  UCA0TXBUF = UCA0RXBUF;                    // TX -> RXed character, echo the character
}
