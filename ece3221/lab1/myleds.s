/***
CMPE3221 LAB#1 - MY FIRST NIOS-II PROGRAM
-----------------------------------------------
DATE: September 10 NAME: Jacob Smith
-----------------------------------------------
This program reads a value from 16 switches
and writes the value to 16 LEDs
-----------------------------------------------
PORT MAP
0x00008850 = 16-bit input port = SWITCHES
0x00008880 = 16-bit output port = LEDS
-----------------------------------------------
***/

.global _start

_start: ori r10, r0, 0x8850 # r10 = address of switches
        ori r11, r0, 0x8880 # r11 = address of red LEDs
		
		ori r13, r0, 0x8930 # r13 = address of port PD
		ori r14, r0, 0x8934 # r14 = address of control register for port PD
		
		ori r16, r0, 0x88A0 # r16 = address of the hex display
		ori r17, r0, 0x88B0 # r17 = address of the hex display control register
		
		ori r2,  r0, 0x000F # r2 = value for 3..0 output & 4..7 input
		sthio r2, 0(r14)    # setting PD port 3..0 = ouput & 4..7 = input
		
		ori r2,  r0, 0x0103 # value to enable HEX1..HEX0 & the DISPLAY
		sthio r2, 0(r17)    # enabling HEX1..HEX0 & the DISPLAY

top:    ldhio r2, 0(r10)    # read the 16 switches
		andi r2, r2, 0xF    # ignore switches 4..
        sthio r2, 0(r13)    # write switches 0..3 to port PD
		
		ldhio r2, 0(r13)    # read the 8-bit value of port PD
		sthio r2, 0(r11)	# write the value to the red LEDs
		sthio r2, 0(r16)    # write the value to the hex display
        
		br top              # repeat forever

# -----------------------------------------------
