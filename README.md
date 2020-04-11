# RGB_LED_Controller
5V RGB LED Controller using PIC16F15356 with Python GUI

### Microcontroller
Used a PIC16F15356; Configured via MCC; Waits for the following sequence in UART1 (9600)

**['s']['.'][red][.][blue][.][green]['.']['e']**

Legend:

Value enclosed with [] is a byte, for colors (rgb) max is 4 bytes.

Value enclosed with '' is a character

### Python GUI
Sends the value of R,G,B in string to UART COM6 (hard-coded for now; will customized later)

