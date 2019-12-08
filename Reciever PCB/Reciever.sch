EESchema Schematic File Version 4
EELAYER 29 0
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
L MCU_Module:Arduino_Nano_v2.x A1
U 1 1 5DB5E139
P 2200 3300
F 0 "A1" H 2200 2211 50  0000 C CNN
F 1 "Arduino_Nano_v2.x" H 2200 2120 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 2350 2350 50  0001 L CNN
F 3 "https://www.arduino.cc/en/uploads/Main/ArduinoNanoManual23.pdf" H 2200 2300 50  0001 C CNN
	1    2200 3300
	1    0    0    -1  
$EndComp
$Comp
L Sensor:DHT11 U1
U 1 1 5DB5EEDB
P 3350 3900
F 0 "U1" H 3106 3946 50  0000 R CNN
F 1 "DHT11" H 3106 3855 50  0000 R CNN
F 2 "Sensor:Aosong_DHT11_5.5x12.0_P2.54mm" H 3350 3500 50  0001 C CNN
F 3 "http://akizukidenshi.com/download/ds/aosong/DHT11.pdf" H 3500 4150 50  0001 C CNN
	1    3350 3900
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D1
U 1 1 5DB5F67A
P 3350 2550
F 0 "D1" H 3343 2766 50  0000 C CNN
F 1 "LED" H 3343 2675 50  0000 C CNN
F 2 "LED_SMD:LED_Cree-XB" H 3350 2550 50  0001 C CNN
F 3 "~" H 3350 2550 50  0001 C CNN
	1    3350 2550
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D2
U 1 1 5DB60107
P 3350 3100
F 0 "D2" H 3343 3316 50  0000 C CNN
F 1 "LED" H 3343 3225 50  0000 C CNN
F 2 "LED_SMD:LED_Cree-XB" H 3350 3100 50  0001 C CNN
F 3 "~" H 3350 3100 50  0001 C CNN
	1    3350 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 2550 3200 1900
Wire Wire Line
	3200 1900 1450 1900
Wire Wire Line
	1450 3000 1700 3000
Wire Wire Line
	1450 1900 1450 3000
Wire Wire Line
	3200 3100 3150 3100
Wire Wire Line
	3150 3100 3150 2000
Wire Wire Line
	3150 2000 1550 2000
Wire Wire Line
	1550 2000 1550 2900
Wire Wire Line
	1550 2900 1700 2900
Wire Wire Line
	3350 3600 3350 3200
Wire Wire Line
	3350 3200 3000 3200
Wire Wire Line
	3000 3200 3000 2200
Wire Wire Line
	3000 2200 2400 2200
Wire Wire Line
	2400 2200 2400 2300
Wire Wire Line
	3500 2550 3800 2550
Wire Wire Line
	3800 2550 3800 3100
Wire Wire Line
	3800 4450 3350 4450
Wire Wire Line
	2300 4450 2300 4300
Wire Wire Line
	3350 4200 3350 4450
Connection ~ 3350 4450
Wire Wire Line
	3350 4450 2300 4450
Wire Wire Line
	3500 3100 3800 3100
Connection ~ 3800 3100
Wire Wire Line
	3800 3100 3800 4450
Wire Wire Line
	3650 3900 3650 4550
Wire Wire Line
	3650 4550 1600 4550
Wire Wire Line
	1600 4550 1600 3900
Wire Wire Line
	1600 3900 1700 3900
$EndSCHEMATC
