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
LIBS:Fob-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ATMEGA328P-A IC1
U 1 1 56D1AAD2
P 5750 3250
F 0 "IC1" H 5000 4500 50  0000 L BNN
F 1 "ATMEGA328-P" H 6150 1850 50  0000 L BNN
F 2 "Housings_QFP:TQFP-32_7x7mm_Pitch0.8mm" H 5750 3250 50  0000 C CIN
F 3 "" H 5750 3250 50  0000 C CNN
	1    5750 3250
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH SW1
U 1 1 56D1AB7B
P 7200 4500
F 0 "SW1" H 7350 4610 50  0000 C CNN
F 1 "SW_PUSH" H 7200 4420 50  0000 C CNN
F 2 "fob:SW_PUSH_6mm" H 7200 4500 50  0001 C CNN
F 3 "" H 7200 4500 50  0000 C CNN
	1    7200 4500
	0    1    1    0   
$EndComp
$Comp
L Led_Small D1
U 1 1 56D1ACC8
P 7700 3750
F 0 "D1" H 7650 3875 50  0000 L CNN
F 1 "Led_Small" H 7525 3650 50  0000 L CNN
F 2 "LEDs:LED-3MM" V 7700 3750 50  0001 C CNN
F 3 "" V 7700 3750 50  0000 C CNN
	1    7700 3750
	-1   0    0    1   
$EndComp
$Comp
L R R2
U 1 1 56D1AD6E
P 7450 3950
F 0 "R2" V 7530 3950 50  0000 C CNN
F 1 "10K" V 7450 3950 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM7mm" V 7380 3950 50  0001 C CNN
F 3 "" H 7450 3950 50  0000 C CNN
	1    7450 3950
	0    1    1    0   
$EndComp
$Comp
L R R3
U 1 1 56D1ADE5
P 7300 3750
F 0 "R3" V 7380 3750 50  0000 C CNN
F 1 "330" V 7300 3750 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM7mm" V 7230 3750 50  0001 C CNN
F 3 "" H 7300 3750 50  0000 C CNN
	1    7300 3750
	0    -1   -1   0   
$EndComp
$Comp
L R R1
U 1 1 56D1AEE6
P 7050 3600
F 0 "R1" V 7130 3600 50  0000 C CNN
F 1 "10K" V 7050 3600 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM7mm" V 6980 3600 50  0001 C CNN
F 3 "" H 7050 3600 50  0000 C CNN
	1    7050 3600
	0    1    1    0   
$EndComp
$Comp
L CONN_02X04 P1
U 1 1 56D1B6A6
P 5800 1500
F 0 "P1" H 5800 1750 50  0000 C CNN
F 1 "RF24L01" H 5800 1250 50  0000 C CNN
F 2 "fob:Pin_Header_RF24L01" H 5800 300 50  0001 C CNN
F 3 "" H 5800 300 50  0000 C CNN
	1    5800 1500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR01
U 1 1 56D1BAAD
P 4650 1400
F 0 "#PWR01" H 4650 1150 50  0001 C CNN
F 1 "GND" H 4650 1250 50  0000 C CNN
F 2 "" H 4650 1400 50  0000 C CNN
F 3 "" H 4650 1400 50  0000 C CNN
	1    4650 1400
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR02
U 1 1 56D1BC36
P 4100 2100
F 0 "#PWR02" H 4100 1950 50  0001 C CNN
F 1 "VCC" H 4100 2250 50  0000 C CNN
F 2 "" H 4100 2100 50  0000 C CNN
F 3 "" H 4100 2100 50  0000 C CNN
	1    4100 2100
	1    0    0    -1  
$EndComp
NoConn ~ 6050 1650
$Comp
L VCC #PWR03
U 1 1 56D1BF3F
P 7400 3600
F 0 "#PWR03" H 7400 3450 50  0001 C CNN
F 1 "VCC" H 7400 3750 50  0000 C CNN
F 2 "" H 7400 3600 50  0000 C CNN
F 3 "" H 7400 3600 50  0000 C CNN
	1    7400 3600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 56D1C504
P 8000 3950
F 0 "#PWR04" H 8000 3700 50  0001 C CNN
F 1 "GND" H 8000 3800 50  0000 C CNN
F 2 "" H 8000 3950 50  0000 C CNN
F 3 "" H 8000 3950 50  0000 C CNN
	1    8000 3950
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR05
U 1 1 56D1C968
P 7200 4950
F 0 "#PWR05" H 7200 4800 50  0001 C CNN
F 1 "VCC" H 7200 5100 50  0000 C CNN
F 2 "" H 7200 4950 50  0000 C CNN
F 3 "" H 7200 4950 50  0000 C CNN
	1    7200 4950
	-1   0    0    1   
$EndComp
$Comp
L Battery BT1
U 1 1 56D1CE95
P 2400 2700
F 0 "BT1" H 2500 2750 50  0000 L CNN
F 1 "CR2032" H 2500 2650 50  0000 L CNN
F 2 "fob:CR2032" V 2400 2740 50  0001 C CNN
F 3 "" V 2400 2740 50  0000 C CNN
	1    2400 2700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 56D1CFF0
P 2400 3100
F 0 "#PWR06" H 2400 2850 50  0001 C CNN
F 1 "GND" H 2400 2950 50  0000 C CNN
F 2 "" H 2400 3100 50  0000 C CNN
F 3 "" H 2400 3100 50  0000 C CNN
	1    2400 3100
	1    0    0    -1  
$EndComp
$Comp
L C_Small C1
U 1 1 56D1D350
P 4600 2300
F 0 "C1" H 4610 2370 50  0000 L CNN
F 1 "100n" H 4610 2220 50  0000 L CNN
F 2 "fob:C_Disc_P5" H 4600 2300 50  0001 C CNN
F 3 "" H 4600 2300 50  0000 C CNN
	1    4600 2300
	0    1    1    0   
$EndComp
$Comp
L C_Small C2
U 1 1 56D1D46D
P 4750 2600
F 0 "C2" H 4760 2670 50  0000 L CNN
F 1 "100n" H 4760 2520 50  0000 L CNN
F 2 "fob:C_Disc_P5" H 4750 2600 50  0001 C CNN
F 3 "" H 4750 2600 50  0000 C CNN
	1    4750 2600
	0    1    1    0   
$EndComp
NoConn ~ 6750 2750
NoConn ~ 6750 2850
NoConn ~ 6750 3000
NoConn ~ 6750 3100
NoConn ~ 6750 3200
NoConn ~ 6750 3300
NoConn ~ 6750 3400
NoConn ~ 6750 3500
NoConn ~ 6750 3850
NoConn ~ 6750 4050
NoConn ~ 6750 4150
NoConn ~ 6750 4250
NoConn ~ 6750 4350
NoConn ~ 6750 4450
$Comp
L GND #PWR07
U 1 1 56D20558
P 4700 4450
F 0 "#PWR07" H 4700 4200 50  0001 C CNN
F 1 "GND" H 4700 4300 50  0000 C CNN
F 2 "" H 4700 4450 50  0000 C CNN
F 3 "" H 4700 4450 50  0000 C CNN
	1    4700 4450
	0    1    1    0   
$EndComp
$Comp
L VCC #PWR08
U 1 1 56D20B3A
P 6200 1350
F 0 "#PWR08" H 6200 1200 50  0001 C CNN
F 1 "VCC" H 6200 1500 50  0000 C CNN
F 2 "" H 6200 1350 50  0000 C CNN
F 3 "" H 6200 1350 50  0000 C CNN
	1    6200 1350
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #VCC09
U 1 1 56D210D3
P 2400 1200
F 0 "#VCC09" H 2400 1295 50  0001 C CNN
F 1 "PWR_FLAG" H 2400 1380 50  0000 C CNN
F 2 "" H 2400 1200 50  0000 C CNN
F 3 "" H 2400 1200 50  0000 C CNN
	1    2400 1200
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR010
U 1 1 56D1CFC6
P 2400 2250
F 0 "#PWR010" H 2400 2100 50  0001 C CNN
F 1 "VCC" H 2400 2400 50  0000 C CNN
F 2 "" H 2400 2250 50  0000 C CNN
F 3 "" H 2400 2250 50  0000 C CNN
	1    2400 2250
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #GND011
U 1 1 56D217B5
P 2900 1200
F 0 "#GND011" H 2900 1295 50  0001 C CNN
F 1 "PWR_FLAG" H 2900 1380 50  0000 C CNN
F 2 "" H 2900 1200 50  0000 C CNN
F 3 "" H 2900 1200 50  0000 C CNN
	1    2900 1200
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR012
U 1 1 56D217DF
P 2400 1450
F 0 "#PWR012" H 2400 1300 50  0001 C CNN
F 1 "VCC" H 2400 1600 50  0000 C CNN
F 2 "" H 2400 1450 50  0000 C CNN
F 3 "" H 2400 1450 50  0000 C CNN
	1    2400 1450
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR013
U 1 1 56D21809
P 2900 1450
F 0 "#PWR013" H 2900 1200 50  0001 C CNN
F 1 "GND" H 2900 1300 50  0000 C CNN
F 2 "" H 2900 1450 50  0000 C CNN
F 3 "" H 2900 1450 50  0000 C CNN
	1    2900 1450
	1    0    0    -1  
$EndComp
$Comp
L C_Small C3
U 1 1 56D1D4FE
P 4650 2950
F 0 "C3" H 4660 3020 50  0000 L CNN
F 1 "100n" H 4660 2870 50  0000 L CNN
F 2 "fob:C_Disc_P5" H 4650 2950 50  0001 C CNN
F 3 "" H 4650 2950 50  0000 C CNN
	1    4650 2950
	0    1    1    0   
$EndComp
$Comp
L GND #PWR014
U 1 1 56D20D48
P 4350 2950
F 0 "#PWR014" H 4350 2700 50  0001 C CNN
F 1 "GND" H 4350 2800 50  0000 C CNN
F 2 "" H 4350 2950 50  0000 C CNN
F 3 "" H 4350 2950 50  0000 C CNN
	1    4350 2950
	1    0    0    -1  
$EndComp
$Comp
L CONN_02X03 P2
U 1 1 56D1CEAB
P 9200 2400
F 0 "P2" H 9200 2600 50  0000 C CNN
F 1 "ICSP" H 9200 2200 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x03" H 9200 1200 50  0001 C CNN
F 3 "" H 9200 1200 50  0000 C CNN
	1    9200 2400
	0    1    1    0   
$EndComp
$Comp
L GND #PWR015
U 1 1 56D1CF31
P 9300 2000
F 0 "#PWR015" H 9300 1750 50  0001 C CNN
F 1 "GND" H 9300 1850 50  0000 C CNN
F 2 "" H 9300 2000 50  0000 C CNN
F 3 "" H 9300 2000 50  0000 C CNN
	1    9300 2000
	-1   0    0    1   
$EndComp
$Comp
L VCC #PWR016
U 1 1 56D1D04D
P 9100 2000
F 0 "#PWR016" H 9100 1850 50  0001 C CNN
F 1 "VCC" H 9100 2150 50  0000 C CNN
F 2 "" H 9100 2000 50  0000 C CNN
F 3 "" H 9100 2000 50  0000 C CNN
	1    9100 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5550 1350 4650 1350
Wire Wire Line
	4650 1350 4650 1400
Wire Wire Line
	5550 1450 5250 1450
Wire Wire Line
	5250 1450 5250 1950
Wire Wire Line
	5250 1950 6900 1950
Wire Wire Line
	6900 1950 6900 2250
Wire Wire Line
	6900 2250 6750 2250
Wire Wire Line
	5550 1550 5350 1550
Wire Wire Line
	5350 1550 5350 1900
Wire Wire Line
	5350 1900 7050 1900
Wire Wire Line
	7050 1900 7050 2900
Wire Wire Line
	7050 2650 6750 2650
Wire Wire Line
	5550 1650 5550 1850
Wire Wire Line
	5550 1850 7200 1850
Wire Wire Line
	7200 1850 7200 2650
Wire Wire Line
	7200 2550 6750 2550
Wire Wire Line
	6050 1450 7300 1450
Wire Wire Line
	7300 1450 7300 2350
Wire Wire Line
	7300 2350 6750 2350
Wire Wire Line
	6050 1550 6950 1550
Wire Wire Line
	6950 1550 6950 2450
Wire Wire Line
	6750 2450 8650 2450
Wire Wire Line
	6750 3600 6900 3600
Wire Wire Line
	7200 3600 7400 3600
Wire Wire Line
	6750 3950 7300 3950
Wire Wire Line
	7600 3950 8000 3950
Wire Wire Line
	7200 4200 7200 3950
Connection ~ 7200 3950
Wire Wire Line
	7200 4800 7200 4950
Connection ~ 8000 3950
Wire Wire Line
	2400 2850 2400 3100
Wire Wire Line
	4700 4450 4850 4450
Wire Wire Line
	6050 1350 6200 1350
Wire Wire Line
	4350 2600 4650 2600
Wire Wire Line
	4850 2600 4850 2450
Wire Wire Line
	2400 2250 2400 2550
Wire Wire Line
	2400 1200 2400 1450
Wire Wire Line
	2900 1200 2900 1450
Wire Wire Line
	4350 2950 4550 2950
Wire Wire Line
	4800 2950 4750 2950
Wire Wire Line
	4800 2750 4800 2950
Wire Wire Line
	4800 2750 4850 2750
Wire Wire Line
	4850 2450 4100 2450
Wire Wire Line
	4100 2450 4100 2100
Wire Wire Line
	4100 2150 4850 2150
Connection ~ 4100 2150
Wire Wire Line
	4350 2300 4350 2950
Connection ~ 4350 2600
Wire Wire Line
	4700 4250 4700 4450
Wire Wire Line
	9100 2000 9100 2150
Wire Wire Line
	9200 2150 9200 1650
Wire Wire Line
	9200 1650 8650 1650
Wire Wire Line
	8650 1650 8650 2450
Wire Wire Line
	9300 2650 9300 3350
Wire Wire Line
	9300 3350 6850 3350
Wire Wire Line
	6850 3350 6850 3600
Connection ~ 6850 3600
Wire Wire Line
	9200 2650 9200 2900
Wire Wire Line
	9200 2900 7050 2900
Connection ~ 7050 2650
Wire Wire Line
	7200 2650 9100 2650
Connection ~ 7200 2550
Connection ~ 6950 2450
Wire Wire Line
	4700 2300 4700 2150
Connection ~ 4700 2150
Wire Wire Line
	4850 2250 4800 2250
Wire Wire Line
	4800 2250 4800 2150
Connection ~ 4800 2150
Wire Wire Line
	4500 2300 4350 2300
NoConn ~ 4850 3500
NoConn ~ 4850 3600
Wire Wire Line
	4850 4250 4700 4250
Wire Wire Line
	4850 4350 4700 4350
Connection ~ 4700 4350
Wire Wire Line
	9300 2150 9300 2000
Wire Wire Line
	7800 3750 8000 3750
Wire Wire Line
	8000 3750 8000 3950
Wire Wire Line
	7450 3750 7600 3750
Wire Wire Line
	6750 3750 7150 3750
NoConn ~ 6750 2150
NoConn ~ 5000 2000
NoConn ~ 6950 4000
NoConn ~ 6700 2250
NoConn ~ 6900 2150
$Comp
L C_Small C4
U 1 1 56DA8E6B
P 2000 2700
F 0 "C4" H 2010 2770 50  0000 L CNN
F 1 "10uF" H 2010 2620 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Radial_D5_L6_P2.5" H 2000 2700 50  0001 C CNN
F 3 "" H 2000 2700 50  0000 C CNN
	1    2000 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 2600 2000 2400
Wire Wire Line
	2000 2400 2400 2400
Connection ~ 2400 2400
Wire Wire Line
	2000 2800 2000 3000
Wire Wire Line
	2000 3000 2400 3000
Connection ~ 2400 3000
$Comp
L SW_PUSH SW2
U 1 1 56DAD8F4
P 8700 4350
F 0 "SW2" H 8850 4460 50  0000 C CNN
F 1 "SW_PUSH" H 8700 4270 50  0000 C CNN
F 2 "fob:SW_PUSH_6mm" H 8700 4350 50  0001 C CNN
F 3 "" H 8700 4350 50  0000 C CNN
	1    8700 4350
	0    1    1    0   
$EndComp
$Comp
L GND #PWR017
U 1 1 56DAD958
P 8700 4850
F 0 "#PWR017" H 8700 4600 50  0001 C CNN
F 1 "GND" H 8700 4700 50  0000 C CNN
F 2 "" H 8700 4850 50  0000 C CNN
F 3 "" H 8700 4850 50  0000 C CNN
	1    8700 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	8700 4850 8700 4650
Wire Wire Line
	8700 3350 8700 4050
Connection ~ 8700 3350
$EndSCHEMATC