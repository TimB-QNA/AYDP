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
LIBS:components
LIBS:Baseboard-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "2 jul 2014"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L CONN_8 P?
U 1 1 53A91E63
P 1050 1200
F 0 "P?" V 1000 1200 60  0000 C CNN
F 1 "CONN_8" V 1100 1200 60  0000 C CNN
F 2 "" H 1050 1200 60  0000 C CNN
F 3 "" H 1050 1200 60  0000 C CNN
	1    1050 1200
	-1   0    0    -1  
$EndComp
Text Notes 900  700  0    60   ~ 0
From sensors
$Comp
L CONN_2 P?
U 1 1 53A91E9E
P 1050 3300
F 0 "P?" V 1000 3300 40  0000 C CNN
F 1 "CONN_2" V 1100 3300 40  0000 C CNN
F 2 "" H 1050 3300 60  0000 C CNN
F 3 "" H 1050 3300 60  0000 C CNN
	1    1050 3300
	-1   0    0    1   
$EndComp
$Comp
L CONN_2 P?
U 1 1 53A91EAB
P 1050 2950
F 0 "P?" V 1000 2950 40  0000 C CNN
F 1 "CONN_2" V 1100 2950 40  0000 C CNN
F 2 "" H 1050 2950 60  0000 C CNN
F 3 "" H 1050 2950 60  0000 C CNN
	1    1050 2950
	-1   0    0    1   
$EndComp
Wire Wire Line
	1400 3050 1500 3050
Wire Wire Line
	1500 3050 1500 3200
Wire Wire Line
	1500 3200 1400 3200
Text Label 1500 3400 0    60   ~ 0
0V
Text Label 2500 2950 0    60   ~ 0
VBATT
Wire Wire Line
	1400 2850 1500 2850
Wire Wire Line
	1400 3400 1500 3400
Text Notes 950  3650 0    60   ~ 0
Batteries are split into\n2 sets of 4xAA giving\nnominally 9.6 volts
$Comp
L SWITCH_INV SW?
U 1 1 53A91F5A
P 2000 2850
F 0 "SW?" H 1800 3000 50  0000 C CNN
F 1 "SWITCH_INV" H 1850 2700 50  0000 C CNN
F 2 "~" H 2000 2850 60  0000 C CNN
F 3 "~" H 2000 2850 60  0000 C CNN
	1    2000 2850
	1    0    0    -1  
$EndComp
$Comp
L CONN_2 P?
U 1 1 53A91F72
P 1850 2450
F 0 "P?" V 1800 2450 40  0000 C CNN
F 1 "CONN_2" V 1900 2450 40  0000 C CNN
F 2 "" H 1850 2450 60  0000 C CNN
F 3 "" H 1850 2450 60  0000 C CNN
	1    1850 2450
	1    0    0    -1  
$EndComp
Text Label 1300 2350 0    60   ~ 0
0V
Wire Wire Line
	1300 2350 1500 2350
Text Notes 2000 2450 0    60   ~ 0
Charging socket
Text Label 1500 850  0    60   ~ 0
0V
Text Label 1500 950  0    60   ~ 0
MOSI
Text Label 1500 1050 0    60   ~ 0
SPI_SEL
Text Label 1500 1150 0    60   ~ 0
MISO
Text Label 1500 1250 0    60   ~ 0
SCLK
Text Label 1500 1350 0    60   ~ 0
PULSE
Text Label 1500 1450 0    60   ~ 0
VBATT
Wire Wire Line
	1400 850  1500 850 
Wire Wire Line
	1400 950  1500 950 
Wire Wire Line
	1400 1050 1500 1050
Wire Wire Line
	1400 1150 1500 1150
Wire Wire Line
	1400 1250 1500 1250
Wire Wire Line
	1400 1350 2000 1350
Wire Wire Line
	1400 1450 1500 1450
$Comp
L ARD_NANO U?
U 1 1 53A929E2
P 5700 1450
F 0 "U?" H 5650 450 60  0000 C CNN
F 1 "ARD_NANO" H 5700 2150 60  0000 C CNN
F 2 "" H 5650 1450 60  0000 C CNN
F 3 "" H 5650 1450 60  0000 C CNN
	1    5700 1450
	1    0    0    -1  
$EndComp
Text Label 6350 900  0    60   ~ 0
VBATT
Text Label 6350 1000 0    60   ~ 0
0V
Text Label 4900 1200 0    60   ~ 0
0V
Wire Wire Line
	4900 1200 5100 1200
Wire Wire Line
	6250 1000 6350 1000
Wire Wire Line
	6250 900  6750 900 
Text Label 4800 2300 0    60   ~ 0
MISO
Text Label 4800 2200 0    60   ~ 0
MOSI
Text Label 4800 2100 0    60   ~ 0
CS
Text Label 6350 2300 0    60   ~ 0
SCLK
Wire Wire Line
	6250 2300 6350 2300
Wire Wire Line
	5100 2300 4800 2300
Wire Wire Line
	4800 2200 5100 2200
Wire Wire Line
	4800 2100 5100 2100
$Comp
L PS-2801_OPTOCOUPLER U?
U 1 1 53A92B59
P 8650 1050
F 0 "U?" H 8850 1300 60  0000 C CNN
F 1 "PS-2801_OPTOCOUPLER" H 8600 1400 60  0000 C CNN
F 2 "~" H 8650 650 60  0000 C CNN
F 3 "~" H 8650 650 60  0000 C CNN
	1    8650 1050
	1    0    0    -1  
$EndComp
Text Label 7300 900  2    60   ~ 0
BT_TXD
$Comp
L R R?
U 1 1 53A92B85
P 7650 900
F 0 "R?" V 7730 900 40  0000 C CNN
F 1 "330R" V 7657 901 40  0000 C CNN
F 2 "~" V 7580 900 30  0000 C CNN
F 3 "~" H 7650 900 30  0000 C CNN
	1    7650 900 
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7300 900  7400 900 
Wire Wire Line
	7900 900  8000 900 
Text Label 7800 1200 0    60   ~ 0
0V
Wire Wire Line
	7800 1200 8000 1200
Text Label 9400 1200 0    60   ~ 0
A_RXD
Text Label 4700 1600 0    60   ~ 0
A_RXD
Wire Wire Line
	9250 1200 10500 1200
Text Label 6350 1200 0    60   ~ 0
5V
Wire Wire Line
	6250 1200 6350 1200
Text Label 9400 900  0    60   ~ 0
5V
$Comp
L R R?
U 1 1 53A92C1D
P 10500 1450
F 0 "R?" V 10580 1450 40  0000 C CNN
F 1 "10k" V 10507 1451 40  0000 C CNN
F 2 "~" V 10430 1450 30  0000 C CNN
F 3 "~" H 10500 1450 30  0000 C CNN
	1    10500 1450
	1    0    0    -1  
$EndComp
Text Label 10600 1700 0    60   ~ 0
0V
Wire Wire Line
	10350 1700 10600 1700
Wire Wire Line
	9250 900  9400 900 
Text Label 4700 1500 0    60   ~ 0
A_TXD
Connection ~ 7950 1200
$Comp
L R R?
U 1 1 53A92D3C
P 7650 1300
F 0 "R?" V 7730 1300 40  0000 C CNN
F 1 "330R" V 7657 1301 40  0000 C CNN
F 2 "~" V 7580 1300 30  0000 C CNN
F 3 "~" H 7650 1300 30  0000 C CNN
	1    7650 1300
	0    -1   -1   0   
$EndComp
Text Label 7300 1300 2    60   ~ 0
BT_ST
Wire Wire Line
	7300 1300 7400 1300
$Comp
L R R?
U 1 1 53A92DB4
P 10050 1600
F 0 "R?" V 10130 1600 40  0000 C CNN
F 1 "10k" V 10057 1601 40  0000 C CNN
F 2 "~" V 9980 1600 30  0000 C CNN
F 3 "~" H 10050 1600 30  0000 C CNN
	1    10050 1600
	0    -1   -1   0   
$EndComp
Wire Wire Line
	10300 1600 10350 1600
Wire Wire Line
	10350 1600 10350 1700
Connection ~ 10500 1700
Wire Wire Line
	9800 1600 9250 1600
Wire Wire Line
	9300 900  9300 1300
Wire Wire Line
	9300 1300 9250 1300
Connection ~ 9300 900 
Text Label 9400 1600 0    60   ~ 0
A_ST
Wire Wire Line
	7900 1300 8000 1300
Wire Wire Line
	7950 1200 7950 1600
Wire Wire Line
	7950 1600 8000 1600
Text Label 4700 1400 0    60   ~ 0
A_ST
Wire Wire Line
	4700 1300 5100 1300
$Comp
L CONN_6 P?
U 1 1 53A92EBF
P 2850 1250
F 0 "P?" V 2800 1250 60  0000 C CNN
F 1 "CONN_6" V 2900 1250 60  0000 C CNN
F 2 "" H 2850 1250 60  0000 C CNN
F 3 "" H 2850 1250 60  0000 C CNN
	1    2850 1250
	-1   0    0    -1  
$EndComp
Text Label 3300 1000 0    60   ~ 0
KEY
Text Label 3300 1100 0    60   ~ 0
5V
Text Label 3300 1200 0    60   ~ 0
GND
Text Label 3300 1300 0    60   ~ 0
BT_TXD
Text Label 3300 1400 0    60   ~ 0
BT_RXD
Text Label 3300 1500 0    60   ~ 0
BT_ST
Wire Wire Line
	3200 1000 3300 1000
Wire Wire Line
	3200 1100 3300 1100
Wire Wire Line
	3200 1200 3300 1200
Wire Wire Line
	3200 1300 3300 1300
Wire Wire Line
	3200 1500 3300 1500
Text Notes 2700 850  0    60   ~ 0
Serial to Bluetooth
$Comp
L R R?
U 1 1 53A92FE8
P 4200 1250
F 0 "R?" V 4280 1250 40  0000 C CNN
F 1 "1k7" V 4207 1251 40  0000 C CNN
F 2 "~" V 4130 1250 30  0000 C CNN
F 3 "~" H 4200 1250 30  0000 C CNN
	1    4200 1250
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 53A92FF5
P 4200 1750
F 0 "R?" V 4280 1750 40  0000 C CNN
F 1 "3k3" V 4207 1751 40  0000 C CNN
F 2 "~" V 4130 1750 30  0000 C CNN
F 3 "~" H 4200 1750 30  0000 C CNN
	1    4200 1750
	1    0    0    -1  
$EndComp
Text Label 4000 2000 0    60   ~ 0
0V
Wire Wire Line
	4000 2000 4200 2000
Wire Wire Line
	3750 1500 4200 1500
$Comp
L MOSFET_N Q?
U 1 1 53A93126
P 8750 4250
F 0 "Q?" H 8760 4420 60  0000 R CNN
F 1 "MOSFET_N" H 8760 4100 60  0000 R CNN
F 2 "~" H 8750 4250 60  0000 C CNN
F 3 "~" H 8750 4250 60  0000 C CNN
	1    8750 4250
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 53A93135
P 8850 3200
F 0 "R?" V 8930 3200 40  0000 C CNN
F 1 "500R" V 8857 3201 40  0000 C CNN
F 2 "~" V 8780 3200 30  0000 C CNN
F 3 "~" H 8850 3200 30  0000 C CNN
	1    8850 3200
	1    0    0    -1  
$EndComp
$Comp
L LED D?
U 1 1 53A93144
P 8850 3750
F 0 "D?" H 8850 3850 50  0000 C CNN
F 1 "LED" H 8850 3650 50  0000 C CNN
F 2 "~" H 8850 3750 60  0000 C CNN
F 3 "~" H 8850 3750 60  0000 C CNN
	1    8850 3750
	0    1    1    0   
$EndComp
Wire Wire Line
	8850 3450 8850 3550
Wire Wire Line
	8850 3950 8850 4050
Text Label 8850 2850 0    60   ~ 0
5V
Wire Wire Line
	8850 2850 8850 2950
$Comp
L R R?
U 1 1 53A9320D
P 6750 1700
F 0 "R?" V 6830 1700 40  0000 C CNN
F 1 "1k7" V 6757 1701 40  0000 C CNN
F 2 "~" V 6680 1700 30  0000 C CNN
F 3 "~" H 6750 1700 30  0000 C CNN
	1    6750 1700
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 53A93213
P 6750 1200
F 0 "R?" V 6830 1200 40  0000 C CNN
F 1 "3k3" V 6757 1201 40  0000 C CNN
F 2 "~" V 6680 1200 30  0000 C CNN
F 3 "~" H 6750 1200 30  0000 C CNN
	1    6750 1200
	1    0    0    -1  
$EndComp
Text Label 6850 1950 0    60   ~ 0
0V
Wire Wire Line
	6750 1450 6600 1450
Wire Wire Line
	6600 1450 6600 2000
Wire Wire Line
	6600 2000 6250 2000
Wire Wire Line
	6750 900  6750 950 
Wire Wire Line
	6750 1950 6850 1950
$Comp
L MOSFET_N Q?
U 1 1 53A932ED
P 9800 4250
F 0 "Q?" H 9810 4420 60  0000 R CNN
F 1 "MOSFET_N" H 9810 4100 60  0000 R CNN
F 2 "~" H 9800 4250 60  0000 C CNN
F 3 "~" H 9800 4250 60  0000 C CNN
	1    9800 4250
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 53A932F3
P 9900 3200
F 0 "R?" V 9980 3200 40  0000 C CNN
F 1 "500R" V 9907 3201 40  0000 C CNN
F 2 "~" V 9830 3200 30  0000 C CNN
F 3 "~" H 9900 3200 30  0000 C CNN
	1    9900 3200
	1    0    0    -1  
$EndComp
$Comp
L LED D?
U 1 1 53A932F9
P 9900 3750
F 0 "D?" H 9900 3850 50  0000 C CNN
F 1 "LED" H 9900 3650 50  0000 C CNN
F 2 "~" H 9900 3750 60  0000 C CNN
F 3 "~" H 9900 3750 60  0000 C CNN
	1    9900 3750
	0    1    1    0   
$EndComp
Wire Wire Line
	9900 3450 9900 3550
Wire Wire Line
	9900 3950 9900 4050
Text Label 9900 2850 0    60   ~ 0
5V
Wire Wire Line
	9900 2850 9900 2950
Text Label 10100 4450 0    60   ~ 0
0V
Text Label 9250 4250 0    60   ~ 0
ST_Ind
Text Label 8100 4250 0    60   ~ 0
PWR_Ind
Wire Wire Line
	8850 4450 10100 4450
Connection ~ 9900 4450
Wire Wire Line
	9250 4250 9600 4250
Wire Wire Line
	8100 4250 8550 4250
Text Label 4700 1800 0    60   ~ 0
PWR_Ind
Text Label 4700 1900 0    60   ~ 0
ST_Ind
Wire Wire Line
	4700 1900 5100 1900
Wire Wire Line
	4700 1800 5100 1800
Text Notes 8950 3650 0    60   ~ 0
Red
Text Notes 10000 3650 0    60   ~ 0
Blue
$Comp
L R R?
U 1 1 53A9349E
P 4100 3300
F 0 "R?" V 4180 3300 40  0000 C CNN
F 1 "10k" V 4107 3301 40  0000 C CNN
F 2 "~" V 4030 3300 30  0000 C CNN
F 3 "~" H 4100 3300 30  0000 C CNN
	1    4100 3300
	1    0    0    -1  
$EndComp
Text Label 6300 1900 0    60   ~ 0
Temp
Wire Wire Line
	6250 1900 6300 1900
Wire Wire Line
	4100 3550 4100 3650
Text Label 4100 2950 0    60   ~ 0
5V
Text Label 4100 4250 0    60   ~ 0
0V
Text Label 5950 3500 0    60   ~ 0
Temp
Connection ~ 4100 3600
Wire Wire Line
	4100 3050 4100 2950
Wire Wire Line
	4100 4150 4100 4250
$Comp
L LM741 U?
U 1 1 53A93730
P 5300 3500
F 0 "U?" H 5450 3650 60  0000 C CNN
F 1 "LM741" H 5450 3750 60  0000 C CNN
F 2 "" H 5300 3500 60  0000 C CNN
F 3 "" H 5300 3500 60  0000 C CNN
	1    5300 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 3500 5950 3500
Text Notes 5350 3100 0    60   ~ 0
Change this 741\nfor a rail-rail 5V amp.
$Comp
L POT RV?
U 1 1 53A937DC
P 4500 3250
F 0 "RV?" H 4500 3150 50  0000 C CNN
F 1 "POT" H 4500 3250 50  0000 C CNN
F 2 "~" H 4500 3250 60  0000 C CNN
F 3 "~" H 4500 3250 60  0000 C CNN
	1    4500 3250
	0    1    1    0   
$EndComp
$Comp
L POT RV?
U 1 1 53A937EB
P 4650 3850
F 0 "RV?" H 4650 3750 50  0000 C CNN
F 1 "POT" H 4650 3850 50  0000 C CNN
F 2 "~" H 4650 3850 60  0000 C CNN
F 3 "~" H 4650 3850 60  0000 C CNN
	1    4650 3850
	0    1    1    0   
$EndComp
Wire Wire Line
	4500 3500 4500 4150
Wire Wire Line
	4500 4150 4100 4150
Wire Wire Line
	4500 3000 4100 3000
Connection ~ 4100 3000
Wire Wire Line
	4650 3250 4700 3250
Wire Wire Line
	4700 3250 4700 3400
Wire Wire Line
	4700 3400 4800 3400
Connection ~ 5850 3500
Wire Wire Line
	4800 3850 4800 3600
Wire Wire Line
	4650 3600 4100 3600
Wire Wire Line
	4650 4100 5850 4100
Wire Wire Line
	5850 4100 5850 3500
Text Notes 4700 4050 0    60   ~ 0
Feedback
Text Notes 4600 3100 0    60   ~ 0
NULL
$Comp
L CONN_1 P?
U 1 1 53A93B7D
P 6000 3600
F 0 "P?" H 6080 3600 40  0000 L CNN
F 1 "CONN_1" H 6000 3655 30  0001 C CNN
F 2 "" H 6000 3600 60  0000 C CNN
F 3 "" H 6000 3600 60  0000 C CNN
	1    6000 3600
	1    0    0    -1  
$EndComp
Text Notes 5950 3750 0    60   ~ 0
Use as test point
Text Notes 5950 4050 0    60   ~ 0
Set at about 2 volts at\ntypical temperature\nand set gain until suitable\nsensitivity is achieved.\nNULL potentiometer\nshould be mounted on\noutside of enclosure.
$Comp
L THERMISTOR TH?
U 1 1 53A93B8D
P 4100 3900
F 0 "TH?" V 4200 3950 50  0000 C CNN
F 1 "THERMISTOR 10k" V 4000 3900 50  0000 C CNN
F 2 "~" H 4100 3900 60  0000 C CNN
F 3 "~" H 4100 3900 60  0000 C CNN
	1    4100 3900
	1    0    0    -1  
$EndComp
Text Label 9350 2000 0    60   ~ 0
BT_RXD
Wire Wire Line
	3200 1400 3300 1400
Wire Wire Line
	1500 2550 1450 2550
Wire Wire Line
	1450 2550 1450 2850
Connection ~ 1450 2850
Wire Wire Line
	1400 1550 2200 1550
Text Label 1500 1550 0    60   ~ 0
DIR
Text Notes 950  1700 0    60   ~ 0
Pin 8 allows\nus to use the\noriginal hardware\nlargely unmodified
$Comp
L R R?
U 1 1 53B3CC9B
P 2000 1100
F 0 "R?" V 2080 1100 40  0000 C CNN
F 1 "3k3" V 2007 1101 40  0000 C CNN
F 2 "~" V 1930 1100 30  0000 C CNN
F 3 "~" H 2000 1100 30  0000 C CNN
	1    2000 1100
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 53B3CCA1
P 2200 1100
F 0 "R?" V 2280 1100 40  0000 C CNN
F 1 "3k3" V 2207 1101 40  0000 C CNN
F 2 "~" V 2130 1100 30  0000 C CNN
F 3 "~" H 2200 1100 30  0000 C CNN
	1    2200 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 1550 2200 1350
Text Label 2250 850  0    60   ~ 0
5V
Wire Wire Line
	2000 850  2250 850 
Connection ~ 2200 850 
Text Label 6300 1800 0    60   ~ 0
DIR
Wire Wire Line
	6250 1800 6300 1800
Text Label 4700 1300 0    60   ~ 0
PULSE
Wire Wire Line
	4700 1400 5100 1400
Text Label 3750 1500 0    60   ~ 0
BT_RXD
Wire Wire Line
	4700 1600 5100 1600
Wire Wire Line
	4450 1500 5100 1500
Wire Wire Line
	4450 1500 4450 950 
Wire Wire Line
	4450 950  4200 950 
Wire Wire Line
	4200 950  4200 1000
$EndSCHEMATC
