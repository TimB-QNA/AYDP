EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Hardware layout"
Date "19 mar 2015"
Rev "1"
Comp "AYDP"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L CONN_13X2 P?
U 1 1 550B295C
P 4600 4100
F 0 "P?" H 4600 4800 60  0000 C CNN
F 1 "CONN_13X2" V 4600 4100 50  0000 C CNN
F 2 "" H 4600 4100 60  0000 C CNN
F 3 "" H 4600 4100 60  0000 C CNN
	1    4600 4100
	1    0    0    -1  
$EndComp
$Comp
L LM7805 U?
U 1 1 550B296B
P 7450 3550
F 0 "U?" H 7600 3354 60  0000 C CNN
F 1 "LM7805" H 7450 3750 60  0000 C CNN
F 2 "" H 7450 3550 60  0000 C CNN
F 3 "" H 7450 3550 60  0000 C CNN
	1    7450 3550
	1    0    0    -1  
$EndComp
Text Label 8000 3500 0    60   ~ 0
PI +5V
Wire Wire Line
	7850 3500 8000 3500
$Comp
L CONN_2 P?
U 1 1 550B29A9
P 6150 3600
F 0 "P?" V 6100 3600 40  0000 C CNN
F 1 "CONN_2" V 6200 3600 40  0000 C CNN
F 2 "" H 6150 3600 60  0000 C CNN
F 3 "" H 6150 3600 60  0000 C CNN
	1    6150 3600
	-1   0    0    1   
$EndComp
$Comp
L LM7805 U?
U 1 1 550B29B6
P 7450 4250
F 0 "U?" H 7600 4054 60  0000 C CNN
F 1 "LM7805" H 7450 4450 60  0000 C CNN
F 2 "" H 7450 4250 60  0000 C CNN
F 3 "" H 7450 4250 60  0000 C CNN
	1    7450 4250
	1    0    0    -1  
$EndComp
Text Label 8000 4200 0    60   ~ 0
SERVO +5V
Wire Wire Line
	7850 4200 8000 4200
Wire Wire Line
	6500 3700 6800 3700
Wire Wire Line
	6800 3700 6800 4600
Wire Wire Line
	6800 4600 7450 4600
Wire Wire Line
	7450 4600 7450 4500
Wire Wire Line
	7450 3800 7450 3900
Wire Wire Line
	7450 3900 6800 3900
Connection ~ 6800 3900
Wire Wire Line
	6500 3500 7050 3500
Wire Wire Line
	6850 3500 6850 4200
Wire Wire Line
	6850 4200 7050 4200
Connection ~ 6850 3500
Text Label 5000 3500 0    60   ~ 0
PI +5V
Text Label 7000 4600 0    60   ~ 0
0V
Text Label 5000 3700 0    60   ~ 0
0V
Text Label 4000 3500 0    60   ~ 0
3v3
Text Label 4000 3600 0    60   ~ 0
SDA
Text Label 4000 3700 0    60   ~ 0
SCL
Text Label 4000 3900 0    60   ~ 0
0V
Text Notes 4350 3300 0    60   ~ 0
Raspberry PI
Text Notes 2950 3200 0    60   ~ 0
MPU-9150\nbreakout\nboard
Text Notes 7850 4400 0    60   ~ 0
Servo Power Suppply\nProvides power to a USB\nPololu Maestro controller
$Comp
L CONN_8 P?
U 1 1 550B2D61
P 2800 3850
F 0 "P?" V 2750 3850 60  0000 C CNN
F 1 "CONN_8" V 2850 3850 60  0000 C CNN
F 2 "" H 2800 3850 60  0000 C CNN
F 3 "" H 2800 3850 60  0000 C CNN
	1    2800 3850
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4000 3600 4200 3600
Wire Wire Line
	4000 3700 4200 3700
Wire Wire Line
	3200 3900 4200 3900
Wire Wire Line
	3150 3500 4200 3500
Text Label 3250 3700 0    60   ~ 0
SCL
Text Label 3250 3800 0    60   ~ 0
SDA
Wire Wire Line
	3250 3700 3150 3700
Wire Wire Line
	3150 3800 3250 3800
Wire Wire Line
	3150 4100 3200 4100
Wire Wire Line
	3200 4100 3200 3600
Wire Wire Line
	3200 3600 3150 3600
Connection ~ 3200 3900
Text Notes 7000 3050 0    60   ~ 0
Regulators mounted to\nheatsinks and screwed\nto the vessel.
Text Notes 4100 4950 0    60   ~ 0
WiFi connection for the PI\nis provided by a WiFi to\nethernet bridge
$EndSCHEMATC
