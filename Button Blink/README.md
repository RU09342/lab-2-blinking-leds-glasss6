# Button Blink
## Stephen Glass

## blink_switch.c
### Compatibility
* MSP430G2553
* MSP430F5529
* MSP430FR2311
* MSP430FR5994
* MSP430FR6989

### Description
blink_switch.c will switch between blinking two LEDs with a 50% duty cycle when the button is pressed. This is an extension of code blink.c. 
This code will allow you to switch between which LED is blinking by pressing a button. 

This file uses interrupts to detect when the button is being pressed. When a button is pressed, it flips a bit for an enable integer variable. When the enable is high, it will blink LED #1 with ~250000uS delay. Inversely, when the enable is low, it will blink LED #2 with ~250000uS delay.

## blink_polling.c
### Compatibility
* MSP430G2553

### Description
blink_polling.c will blink an LEDs with 50% duty when the button is pressed. This file uses the polling method to detect if a button is being pressed. In a infinite loop, the code checks if the button is being pressed down. We then perform a short delay (~5000uS) and then check if the button is still being pressed down (this is to prevent debouncing). After it passes the two checks, we then enable the LED. Using an infinite while loop, we hold the current position until the status of the button is changed (released). These precautions are also to prevent debouncing or unwanted
behavior from pressing a mechanical button.

## blink.c
### Compatibility
* MSP430G2553

### Description
blink.c will blink two LEDs with 50% duty cycle when a button is pressed. This code result is similar to blink_polling.c, however, this version uses interrupts. Using an interrupt, we simply check if the button was pressed. When the button was pressed, we set an enable integer to high. Inside a while loop, when the enable integer is high we set two LEDs to blink with ~250000uS delay.

## For UART control, visit UARTFlash directory