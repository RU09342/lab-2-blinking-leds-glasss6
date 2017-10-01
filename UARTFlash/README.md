# UART Flash (Extra Work)
## Stephen Glass

### Compatibility
* MSP430G2553

### Description
This code will start UART communication between the MSP430G2553 and a PC Serial communication channel. Once the Serial communication is initialized, the user will be able to control the blinking status of LEDs by typing characters with the users keyboard. The code first initializes the UART communication pins and enables an interrupt for receiving transmitted bytes. When the communication interrupt is enabled, it will check the RX buffer for specific characters. The characters ('1','2','3') determine the LEDs which will blink.

### Setup
* Reposition the jumper cables on the MSP430G2553 LaunchPad development board so HW UART is enabled
* Connect a USB cable from the development board to a PC

For the next portion, you will need to install PuTTY to communicate with the Serial port. Open PuTTY:
* Select Serial under connection type
* Ensure baud rate is set to 9600
* Replace the Serial line with the correct COM port #. This can be found in Device manager.

### Usage
When Serial communication is has been established you can type the following characters to blink LEDs:
* '1'
Toggles the flashing of LED P1.0
* '2'
Toggles the flashing of LED P1.6
* '3'
Toggles the flashing of both LED P1.0 and P1.6
