/* 
ECE3221 LAB 2 - THE HEX KEYPAD (part 2)
This is the Starting Code for Lab 2
----------------------------------------------- 
DATE: 22 OCT 2015 		  NAME:  R.Tervo
----------------------------------------------- 
USES UNB EXPANSION BOARD to scan hex keypad
- manually control keypad rows from switches
- displays raw scancodes on the LEDs
- displays raw scancodes on the HEX display
-----------------------------------------------
CONNNECT PORT PD to keypad
-----------------------------------------------
** KEYPAD REQUIRES Vcc FOR PULLUP RESISTORS **
-----------------------------------------------
*/

.include "nios_macros.s"
.global _start

# ===========================================================	
# HEX KEYPAD INTERFACE

	
_start:


#---- initialization

	ori	r3,r0,0x8890 	# R3 = addr of four board LEDs
	ori	r2,r0,0x0800	# R2 = pattern for the LEDs
	sthio	r2,(r3)		# turn on one LED at PORT PD

	ori	r3,r0,0x88B0	# R3 = address of HEX control
	ori	r2,r0,0x01FF	# R2 = pattern = 2 hex digits ON	
	sthio	r2,(r3)		# initialize hex display

	ori	r18,r0,0x88A0 	# R18 = address of HEX display
	ori	r17,r0,0x8880 	# R17 = address of 16 red LEDs
	ori	r16,r0,0x8850 	# R16 = address of 16 switches
	ori	r15,r0,0x8930 	# R15 = base address I/O port PD
	
	ori     r2,r0,0x0F	# r2 = pattern for I/O direction 
	stbio	r2,4(r15)	# set port PD I/O pins = IIIIOOOO
    
#----

top:

	ori 	r12,r0,10000# r12 = count to ten thousand
	or 		r7,r0,r0	# initialize loop counter to 0

	ori	    r2,r0,0x0E  # select only the top row (by setting bit a to 0)
	stbio	r2,(r15)	# send r2 to keypad port
	nop
	nop
	nop
	nop
	ldbio	r3,(r15)	# read into r3 from keypad port
	andi    r4,r3,0xF0  # select only the input ports (7..4) and insert into r4
	ori     r5,r0,0xF0  # set r5 = 0xF0
	bne     r4,r5,bounce# continue only if a button is pressed (the input isn't all high)
	
	ori	    r2,r0,0x0D  # select only the top row (by setting bit a to 0)
	stbio	r2,(r15)	# send r2 to keypad port
	nop
	nop
	nop
	nop
	ldbio	r3,(r15)	# read into r3 from keypad port
	andi    r4,r3,0xF0  # select only the input ports (7..4) and insert into r4
	ori     r5,r0,0xF0  # set r5 = 0xF0
	bne     r4,r5,bounce# continue only if a button is pressed (the input isn't all high)
	
	ori	    r2,r0,0x0B  # select only the top row (by setting bit a to 0)
	stbio	r2,(r15)	# send r2 to keypad port
	nop
	nop
	nop
	nop
	ldbio	r3,(r15)	# read into r3 from keypad port
	andi    r4,r3,0xF0  # select only the input ports (7..4) and insert into r4
	ori     r5,r0,0xF0  # set r5 = 0xF0
	bne     r4,r5,bounce# continue only if a button is pressed (the input isn't all high)
	
	ori	    r2,r0,0x07  # select only the top row (by setting bit a to 0)
	stbio	r2,(r15)	# send r2 to keypad port
	nop
	nop
	nop
	nop
	ldbio	r3,(r15)	# read into r3 from keypad port
	andi    r4,r3,0xF0  # select only the input ports (7..4) and insert into r4
	ori     r5,r0,0xF0  # set r5 = 0xF0
	bne     r4,r5,bounce# continue only if a button is pressed (the input isn't all high)
	
	br	    top			# If no buttons pressed, look again

	#--- model for debounce in hardware
	#--- assumes the latest scancode is already in r3, keypad addr in r15
	
bounce:
	ldbio 	r5,(r15) 	# r5 = reread the input scancode
	bne 	r5,r3, top 	# go back to scanning if different
	addi 	r12,r12,-1	# decrement the counter
	bne 	r12,r0,bounce# repeat 10000 times
	#----
	
lookup:
	ori 	r21,r0,MYTAB# get the address of MYTAB
	add		r9,r21,r7	# r9 = location of scancode to check
	ldbio 	r8,(r9)		# load scancode
	beq 	r3,r8,disp  # if scancode is equal to the array[index], go to display
	
	beq 	r8,r0,disp	# If we ran read null, display the error key
	
	addi 	r7,r7,2 	# Increment r7
	br		lookup		# loop to check the next scancode
	

	
disp:

	addi 	r9,r9,1		# Add 1 to r9 to get the associated number
	ldbio 	r10,(r9)	# Load the value into r10
	
	#--- hint to shift characters into the display register
	slli 	r20,r20,4 	# shift display buffer register
	or 		r20,r20,r10 # include new 4-bit character
	#---
	
	sthio	r3,(r17)	# send keypad values (r3) to LEDs
	stwio	r20,(r18)	# send keypad values (r20) to HEX display
		
wait:
    ldbio	r4,(r15)	# read into r4 from keypad port
    xor     r5,r4,r3 	# xor display keypad value with current keypad value
    beq     r5,r0,wait  # loop until the keypad values change
    
	br	top				# start again

MYTAB:
	.byte 0xEE,1
	.byte 0xDE,2
	.byte 0xBE,3
	.byte 0x7E,0xA
	.byte 0xED,4
	.byte 0xDD,5
	.byte 0xBD,6
	.byte 0x7D,0xB
	.byte 0xEB,7
	.byte 0xDB,8
	.byte 0xBB,9
	.byte 0x7B,0xC
	.byte 0xE7,0xE
	.byte 0xD7,0
	.byte 0xB7,0xF
	.byte 0x77,0xD
	.byte 0x00,0xFF
	
.end
# ===========================================================	
