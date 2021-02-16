This application shows an example of a FreeRTOS application. There are two 
tasks toggling leds and sending a string to UART.

Please configure the board as follow:

 - wire pins P7[1] and P8[0] for LED0.
 - wire pins P7[2] and P8[1] for LED1.
 - pin P8[10] with the pin J13 (SCI) and on PC set baudrate to 38400


