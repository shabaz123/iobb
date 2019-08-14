test-outputs
============

This program outputs a binary encoded number on every GPIO pin on the BBB.
The number is equal to 127 + the pin number.
So, if you probe connector P8 pin number 12 with an oscilloscope, you'll see a signal
which is 1000 1100.
Connector P9 pin 12 will have the same output.

This program is useful for checking that each pin can function as a GPIO output.

If no oscilloscope is available, you can connect an LED and resistor instead. You'll see
brief flickering every few seconds.

