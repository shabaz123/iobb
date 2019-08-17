iobb library
============

Beaglebone black I/O library , using Memory mapped I/O

Simple C I/O library for Beaglebone Black and variants including PocketBeagle

============================
Based on the work of Meng-Lun, Cai (VegetableAvenger) and Shabaz

	V1 	October 2013 - shabaz (iolib) : create basic library 

	V2 	October 2013 - shabaz (iolib) : fix some BUG

	V2.1	November.7 2013 - add some comment and modify function name

	V2.2	November.10 2013 - add GPIO Enable/Disable function (GPIO 1~3)

	V2.3	November.19 2013 - add GPIO Enable/Disable function (GPIO 0)

	V2.4	November.23 2013 - add whole GPIO control function (I/O and direction set)

	V2.5	December.7  2013 - change directory architecture ,add Demo/ and Toolkit/ directory .

	V2.6	December.9  2013 - add simple ePWM module control function in am335x

	V2.7	December.20 2013 - add simple McSPI control function .

	V2.8	March.14 2014 - add ADC application of Arduino Microphone module ,
				and ADC argument calculation toolkit .

	V3.0	August 14 2019 - shabaz - cleaned up compiler warnings and minor changes, and
		                 renamed to iobb
	V3.1	August 17 2019 - shabaz - added PocketBeagle compatibility


=============================================================================================

This library supports simple I/O for beaglebone black, using C.
The Demo directory includes some example applications for this library and circuit layouts.


**How to use :**

        Build libiobb.a and demo and toolkit code:
                make

        Install in /usr/local/lib and /usr/local/include as superuser:
                make install


**Toolkit List :**

	1. GPIO CLK Status toolkit
	2. Expansion Header toolkit
	3. ADC Argument Calculation toolkit


**Demo List :**

	1. LED Demo
	2. LED_GPIO Demo
	3. ADT7301 Demo (Digital Temperature sensor)
	4. Seven-Segment Array Display demo
	5. Debouncing Demo
	6. 4x4 keypad Demo
	7. PWM Demo
	8. Servo Motor Demo
	9. ADC Demo
	10. ADC with Arduino Microphone Demo
	11. I2C Demo
	



