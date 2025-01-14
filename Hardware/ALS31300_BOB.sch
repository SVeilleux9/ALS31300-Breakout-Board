EESchema Schematic File Version 4
EELAYER 30 0
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
L AllegroMicro:ALS31300 U1
U 1 1 6180958A
P 5725 3700
F 0 "U1" H 5725 4125 50  0000 C CNN
F 1 "ALS31300" H 5725 4034 50  0000 C CNN
F 2 "Package_DFN_QFN:DFN-10-1EP_3x3mm_P0.5mm_EP1.75x2.7mm" H 5675 3700 50  0001 C CNN
F 3 "" H 5675 3700 50  0001 C CNN
	1    5725 3700
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0101
U 1 1 61809BDB
P 5325 3500
F 0 "#PWR0101" H 5325 3350 50  0001 C CNN
F 1 "+3.3V" H 5340 3673 50  0000 C CNN
F 2 "" H 5325 3500 50  0001 C CNN
F 3 "" H 5325 3500 50  0001 C CNN
	1    5325 3500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 6180ADF8
P 4825 4125
F 0 "#PWR0102" H 4825 3875 50  0001 C CNN
F 1 "GND" H 4830 3952 50  0000 C CNN
F 2 "" H 4825 4125 50  0001 C CNN
F 3 "" H 4825 4125 50  0001 C CNN
	1    4825 4125
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R2
U 1 1 6180BDBC
P 4825 3900
F 0 "R2" H 4893 3946 50  0000 L CNN
F 1 "10k" H 4893 3855 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4865 3890 50  0001 C CNN
F 3 "~" H 4825 3900 50  0001 C CNN
	1    4825 3900
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 6180CEDE
P 4275 3400
F 0 "C1" H 4390 3446 50  0000 L CNN
F 1 "0.1uF" H 4390 3355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4313 3250 50  0001 C CNN
F 3 "~" H 4275 3400 50  0001 C CNN
	1    4275 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5325 3500 5325 3550
Wire Wire Line
	5325 3550 5375 3550
Wire Wire Line
	5375 3650 4825 3650
Wire Wire Line
	4825 3650 4825 3750
Wire Wire Line
	4825 4050 4825 4125
$Comp
L power:GND #PWR0103
U 1 1 6181B023
P 6625 4400
F 0 "#PWR0103" H 6625 4150 50  0001 C CNN
F 1 "GND" H 6630 4227 50  0000 C CNN
F 2 "" H 6625 4400 50  0001 C CNN
F 3 "" H 6625 4400 50  0001 C CNN
	1    6625 4400
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R7
U 1 1 6181B029
P 6625 4175
F 0 "R7" H 6693 4221 50  0000 L CNN
F 1 "10k" H 6693 4130 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6665 4165 50  0001 C CNN
F 3 "~" H 6625 4175 50  0001 C CNN
	1    6625 4175
	1    0    0    -1  
$EndComp
Wire Wire Line
	6625 4325 6625 4400
$Comp
L Device:R_US R1
U 1 1 6181BA8D
P 4825 3425
F 0 "R1" H 4893 3471 50  0000 L CNN
F 1 "DNP" H 4893 3380 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4865 3415 50  0001 C CNN
F 3 "~" H 4825 3425 50  0001 C CNN
	1    4825 3425
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R6
U 1 1 6181C74F
P 6625 3550
F 0 "R6" H 6693 3596 50  0000 L CNN
F 1 "DNP" H 6693 3505 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6665 3540 50  0001 C CNN
F 3 "~" H 6625 3550 50  0001 C CNN
	1    6625 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	4825 3650 4825 3575
Connection ~ 4825 3650
$Comp
L power:+3.3V #PWR0104
U 1 1 6181F0CE
P 4825 3225
F 0 "#PWR0104" H 4825 3075 50  0001 C CNN
F 1 "+3.3V" H 4840 3398 50  0000 C CNN
F 2 "" H 4825 3225 50  0001 C CNN
F 3 "" H 4825 3225 50  0001 C CNN
	1    4825 3225
	1    0    0    -1  
$EndComp
Wire Wire Line
	4825 3275 4825 3225
Wire Wire Line
	6625 3400 6625 3350
$Comp
L power:GND #PWR0105
U 1 1 61821065
P 5100 4125
F 0 "#PWR0105" H 5100 3875 50  0001 C CNN
F 1 "GND" H 5105 3952 50  0000 C CNN
F 2 "" H 5100 4125 50  0001 C CNN
F 3 "" H 5100 4125 50  0001 C CNN
	1    5100 4125
	1    0    0    -1  
$EndComp
Wire Wire Line
	5375 3750 5100 3750
Wire Wire Line
	5100 3750 5100 4125
$Comp
L power:+3.3V #PWR0106
U 1 1 61821EE2
P 4275 3200
F 0 "#PWR0106" H 4275 3050 50  0001 C CNN
F 1 "+3.3V" H 4290 3373 50  0000 C CNN
F 2 "" H 4275 3200 50  0001 C CNN
F 3 "" H 4275 3200 50  0001 C CNN
	1    4275 3200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 618229AE
P 4275 3600
F 0 "#PWR0107" H 4275 3350 50  0001 C CNN
F 1 "GND" H 4280 3427 50  0000 C CNN
F 2 "" H 4275 3600 50  0001 C CNN
F 3 "" H 4275 3600 50  0001 C CNN
	1    4275 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4275 3600 4275 3550
Wire Wire Line
	4275 3250 4275 3200
$Comp
L Device:R_US R4
U 1 1 61823DEB
P 6175 3550
F 0 "R4" H 6243 3596 50  0000 L CNN
F 1 "10k" H 6243 3505 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6215 3540 50  0001 C CNN
F 3 "~" H 6175 3550 50  0001 C CNN
	1    6175 3550
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R5
U 1 1 618252AE
P 6400 3550
F 0 "R5" H 6468 3596 50  0000 L CNN
F 1 "10k" H 6468 3505 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6440 3540 50  0001 C CNN
F 3 "~" H 6400 3550 50  0001 C CNN
	1    6400 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	6075 3950 6625 3950
Wire Wire Line
	6625 3950 6625 3700
Wire Wire Line
	6625 4025 6625 3950
Connection ~ 6625 3950
Wire Wire Line
	6400 3700 6400 3850
Wire Wire Line
	6400 3850 6075 3850
Wire Wire Line
	6075 3750 6175 3750
Wire Wire Line
	6175 3750 6175 3700
Wire Wire Line
	6175 3400 6175 3350
Wire Wire Line
	6400 3400 6400 3350
$Comp
L Device:R_US R3
U 1 1 6182BF13
P 5275 4125
F 0 "R3" H 5343 4171 50  0000 L CNN
F 1 "10k" H 5343 4080 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5315 4115 50  0001 C CNN
F 3 "~" H 5275 4125 50  0001 C CNN
	1    5275 4125
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0108
U 1 1 6182DF3B
P 5550 4275
F 0 "#PWR0108" H 5550 4125 50  0001 C CNN
F 1 "+3.3V" H 5565 4448 50  0000 C CNN
F 2 "" H 5550 4275 50  0001 C CNN
F 3 "" H 5550 4275 50  0001 C CNN
	1    5550 4275
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0109
U 1 1 6182E994
P 6400 3250
F 0 "#PWR0109" H 6400 3100 50  0001 C CNN
F 1 "+3.3V" H 6415 3423 50  0000 C CNN
F 2 "" H 6400 3250 50  0001 C CNN
F 3 "" H 6400 3250 50  0001 C CNN
	1    6400 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	6175 3350 6400 3350
Wire Wire Line
	6625 3350 6400 3350
Connection ~ 6400 3350
Wire Wire Line
	6400 3350 6400 3250
Wire Wire Line
	5375 3850 5275 3850
Wire Wire Line
	5275 3850 5275 3975
Wire Wire Line
	5275 4275 5550 4275
$Comp
L power:+3.3V #PWR0110
U 1 1 61835C44
P 7425 3275
F 0 "#PWR0110" H 7425 3125 50  0001 C CNN
F 1 "+3.3V" H 7440 3448 50  0000 C CNN
F 2 "" H 7425 3275 50  0001 C CNN
F 3 "" H 7425 3275 50  0001 C CNN
	1    7425 3275
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0111
U 1 1 618369A0
P 7425 3800
F 0 "#PWR0111" H 7425 3550 50  0001 C CNN
F 1 "GND" H 7430 3627 50  0000 C CNN
F 2 "" H 7425 3800 50  0001 C CNN
F 3 "" H 7425 3800 50  0001 C CNN
	1    7425 3800
	1    0    0    -1  
$EndComp
Text Label 6175 3750 0    50   ~ 0
SCL
Text Label 6400 3850 0    50   ~ 0
SDA
Text Label 7425 3450 2    50   ~ 0
SDA
Text Label 7425 3550 2    50   ~ 0
SCL
Wire Wire Line
	7425 3550 7550 3550
Wire Wire Line
	7425 3450 7550 3450
Wire Wire Line
	7425 3275 7425 3350
Wire Wire Line
	7425 3350 7550 3350
Wire Wire Line
	7425 3800 7425 3750
Wire Wire Line
	7425 3750 7550 3750
Text Label 5275 3850 2    50   ~ 0
INT
Text Label 7425 3650 2    50   ~ 0
INT
$Comp
L Connector_Generic:Conn_01x05 J1
U 1 1 6183DB50
P 7750 3550
F 0 "J1" H 7830 3592 50  0000 L CNN
F 1 "Conn_01x05" H 7830 3501 50  0000 L CNN
F 2 "Connector_PinHeader_2.00mm:PinHeader_1x05_P2.00mm_Vertical" H 7750 3550 50  0001 C CNN
F 3 "~" H 7750 3550 50  0001 C CNN
	1    7750 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	7425 3650 7550 3650
$EndSCHEMATC
