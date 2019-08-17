
LIB_PATH = ./BBBio_lib/
DEMO_PATH = ./Demo/
TOOLKIT_PATH = ./Toolkit/
LAB_PATH = ./Lab/


LIBRARIES = iobb

all : libiobb.a LED ADT7301 SEVEN_SCAN SMOTOR LED_GPIO DEBOUNCING 4x4keypad ADC ADC_VOICE GPIO_STATUS EP_STATUS ADC_CALC lcd3-test test-outputs pb-test-outputs test-inputs pb-test-inputs

libiobb.a : ${LIB_PATH}BBBiolib.c ${LIB_PATH}BBBiolib.h BBBiolib_PWMSS.o BBBiolib_McSPI.o BBBiolib_ADCTSC.o i2cfunc.o
	gcc -c ${LIB_PATH}BBBiolib.c -o ${LIB_PATH}BBBiolib.o
	ar -rs ${LIB_PATH}libiobb.a ${LIB_PATH}BBBiolib.o ${LIB_PATH}BBBiolib_PWMSS.o ${LIB_PATH}BBBiolib_McSPI.o ${LIB_PATH}BBBiolib_ADCTSC.o ${LIB_PATH}i2cfunc.o
	cp ${LIB_PATH}libiobb.a ./
	cp ${LIB_PATH}BBBiolib.h ./iobb.h
	cp ${LIB_PATH}BBBiolib_ADCTSC.h ./
	cp ${LIB_PATH}BBBiolib_McSPI.h ./
	cp ${LIB_PATH}BBBiolib_PWMSS.h ./
	cp ${LIB_PATH}i2cfunc.h ./

BBBiolib_PWMSS.o : ${LIB_PATH}BBBiolib_PWMSS.c ${LIB_PATH}BBBiolib_PWMSS.h
	gcc -c ${LIB_PATH}BBBiolib_PWMSS.c -o ${LIB_PATH}BBBiolib_PWMSS.o -W 

BBBiolib_McSPI.o : ${LIB_PATH}BBBiolib_McSPI.c ${LIB_PATH}BBBiolib_PWMSS.h
	gcc -c ${LIB_PATH}BBBiolib_McSPI.c -o ${LIB_PATH}BBBiolib_McSPI.o -W

BBBiolib_ADCTSC.o : ${LIB_PATH}BBBiolib_ADCTSC.c ${LIB_PATH}BBBiolib_ADCTSC.h
	gcc -c ${LIB_PATH}BBBiolib_ADCTSC.c -o ${LIB_PATH}BBBiolib_ADCTSC.o -W

i2cfunc.o : ${LIB_PATH}i2cfunc.c ${LIB_PATH}i2cfunc.h
	gcc -c ${LIB_PATH}i2cfunc.c -o ${LIB_PATH}i2cfunc.o

install :  
	rm -f /usr/local/include/BBBiolib.h
	cp ${LIB_PATH}libiobb.a /usr/local/lib
	cp ${LIB_PATH}BBBiolib.h /usr/local/include/iobb.h
	cp ${LIB_PATH}BBBiolib_ADCTSC.h /usr/local/include
	cp ${LIB_PATH}BBBiolib_McSPI.h /usr/local/include
	cp ${LIB_PATH}BBBiolib_PWMSS.h /usr/local/include
	cp ${LIB_PATH}i2cfunc.h /usr/local/include
	ln -s /usr/local/include/iobb.h /usr/local/include/BBBiolib.h

	

#---------------------------------------------------
# Demo
#---------------------------------------------------

test-outputs: test-io/test-outputs.c libiobb.a
	gcc -o test-outputs test-io/test-outputs.c -I. -L. -liobb

pb-test-outputs: test-io/pb-test-outputs.c libiobb.a
	gcc -o pb-test-outputs test-io/pb-test-outputs.c -I. -L. -liobb

test-inputs: test-io/test-inputs.c libiobb.a
	gcc -o test-inputs test-io/test-inputs.c -I. -L. -liobb

pb-test-inputs: test-io/pb-test-inputs.c libiobb.a
	gcc -o pb-test-inputs test-io/pb-test-inputs.c -I. -L. -liobb

LED : ${DEMO_PATH}Demo_LED/LED.c libiobb.a
	gcc -o LED ${DEMO_PATH}Demo_LED/LED.c -L ${LIB_PATH} -liobb

lcd3-test: ${DEMO_PATH}Demo_I2C/lcd3-test.c libiobb.a
	gcc -o lcd3-test ${DEMO_PATH}Demo_I2C/lcd3-test.c -I. -L ${LIB_PATH} -liobb

ADT7301 : ${DEMO_PATH}Demo_ADT7301/ADT7301.c libiobb.a
	gcc -o ADT7301 ${DEMO_PATH}Demo_ADT7301/ADT7301.c -L ${LIB_PATH} -liobb

ADXL345 :  ${DEMO_PATH}Demo_ADXL345/ADXL345.c libiobb.a
	gcc -o ADXL345 ${DEMO_PATH}Demo_ADXL345/ADXL345.c -L ${LIB_PATH} -liobb
ADXL345_NET :  ${DEMO_PATH}Demo_ADXL345/ADXL345_net.c libiobb.a
	gcc -o ADXL345 ${DEMO_PATH}Demo_ADXL345/ADXL345_net.c -L ${LIB_PATH} -liobb

L3G4200D : ${DEMO_PATH}Demo_L3G4200D/L3G4200D.c libiobb.a
	gcc -o L3G4200D ${DEMO_PATH}Demo_L3G4200D/L3G4200D.c -L ${LIB_PATH} -liobb

SEVEN_SCAN : ${DEMO_PATH}Demo_SevenScan/SevenScan.c libiobb.a
	gcc -o SevenScan ${DEMO_PATH}Demo_SevenScan/SevenScan.c  -L ${LIB_PATH} -liobb

SMOTOR : ${DEMO_PATH}Demo_ServoMotor/ServoMotor.c libiobb.a
	gcc -o SMOTOR ${DEMO_PATH}Demo_ServoMotor/ServoMotor.c -L ${LIB_PATH} -liobb

LED_GPIO : ${DEMO_PATH}Demo_LED_GPIO/LED_GPIO.c libiobb.a
	gcc -o LED_GPIO ${DEMO_PATH}Demo_LED_GPIO/LED_GPIO.c -L ${LIB_PATH} -liobb -pthread

DEBOUNCING : ${DEMO_PATH}Demo_Debouncing/Debouncing.c libiobb.a
	gcc -o Debouncing ${DEMO_PATH}Demo_Debouncing/Debouncing.c -L ${LIB_PATH} -liobb

4x4keypad : ${DEMO_PATH}Demo_4x4keypad/4x4keypad.c libiobb.a
	gcc -o 4x4keypad ${DEMO_PATH}Demo_4x4keypad/4x4keypad.c -L ${LIB_PATH} -liobb

PWM : ${DEMO_PATH}Demo_PWM/PWM.c libiobb.a
	gcc -o PWM ${DEMO_PATH}Demo_PWM/PWM.c -L ${LIB_PATH} -liobb

ADC : ${DEMO_PATH}Demo_ADC/ADC.c libiobb.a
	gcc -o ADC ${DEMO_PATH}Demo_ADC/ADC.c -L ${LIB_PATH} -liobb -lm

ADC_VOICE : ${DEMO_PATH}Demo_ADC/ADC_voice.c libiobb.a
	gcc -o ADC_VOICE ${DEMO_PATH}Demo_ADC/ADC_voice.c -L ${LIB_PATH} -liobb -lm -pthread -O3



#---------------------------------------------------
# toolkit 
#---------------------------------------------------

GPIO_STATUS : ${TOOLKIT_PATH}Toolkit_GPIO_CLK_Status/GPIO_status.c libiobb.a
	gcc -o GPIO_CLK_status ${TOOLKIT_PATH}Toolkit_GPIO_CLK_Status/GPIO_status.c  -L ${LIB_PATH} -liobb

EP_STATUS : ${TOOLKIT_PATH}Toolkit_EP_Status/EP_status.c libiobb.a
	gcc -o EP_status ${TOOLKIT_PATH}Toolkit_EP_Status/EP_status.c -L ${LIB_PATH} -liobb


ADC_CALC : ${TOOLKIT_PATH}Toolkit_ADC_CALC/ADC_CALC.c
	gcc -o ADC_CALC ${TOOLKIT_PATH}Toolkit_ADC_CALC/ADC_CALC.c


#---------------------------------------------------
# Lab
#---------------------------------------------------

RA : ${LAB_PATH}Lab_Robot_Arm/Robot_Arm.c libiobb.a
	gcc -o RA  ${LAB_PATH}Lab_Robot_Arm/Robot_Arm.c -L ${LIB_PATH} -liobb -lm

VD : ${LAB_PATH}Voice_Door/voice_door.cpp libiobb.a
	g++ -o VD ${LAB_PATH}Voice_Door/voice_door.cpp -L ${LIB_PATH} -liobb -lfftw3 -lm -pthread -O3


.PHONY: clean
clean :
	rm -rf ${LIB_PATH}*.o ${LIB_PATH}libiobb.a libiobb.a iobb.h BBBiolib_ADCTSC.h BBBiolib_McSPI.h i2cfunc.h lcd3-test test-inputs pb-test-inputs test-outputs pb-test-outputs BBBiolib_PWMSS.h LED ADT7301 GPIO_CLK_status SevenScan Ultrasonic28015 TMP SMOTOR LED_GPIO Debouncing 4x4keypad EP_status PWM RA ADXL345 ADC ADC_CALC L3G4200D

