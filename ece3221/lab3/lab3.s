.global _start

.macro push rx
	addi sp ,sp ,-4
	stw \rx ,0(sp)
.endm

.macro pop rx
	ldw \rx ,0(sp)
	addi sp ,sp ,4
.endm

# ECE3221 LAB#3 - SUBROUTINES
#-----------------------------------------------
#DATE: Oct 2017 NAME: R.Tervo
#-----------------------------------------------

#A Slot Machine
#- rapidly display four counting digits
#- each digits stops when its button is pressed
#- when all stops, four cherries wins
# (any four digits, all the same)
#-----------------------------------------------
#*/

#/*** definitions for push and pop macros go here ***/

# set loop delay in msec (vary speed of the digits)
	.equ N, 20000

_start:

	call init 				# perform initialization

top:

	ori r3,r0,N 				# wait here for N msec
	call delay
	call buttons 				# check buttons now
	beq r5,r0,four 			# done if all digits stopped
	ori r9,r0,4				# Set counter to increment all 4 displays
increment:
	addi r9,r9,-1				# Decrement counter
	ori r4, r0, 1				# Initialize mask
	ori r22,r0,code 			# point to digit
	add r22,r22,r9				# Offset code to get the right index
	sll r4,r4,r9 				# Shift to correct mask
	and r3,r4,r5 				# check if digit is enabled
	beq r3,r0,skipped 			# skip increment if not enabled
	call incx
skipped:
	bne r9,r0,increment			# Loop until all 4 displays are updated

a1:

	call show4 				# update the display
	br top 					# start over

four:

	call check4 				# fireworks if match found
	call switch0 				# wait here for edge on SW0
	ori r5,r0,0x0F 			# re-enable count on all digits
	call reset4 				# reset display digit values
	br top 					# start over

#Shanece Wilson
#Matthew Sampson
#Creates stack of 200 bytes and points sp to it
#initializes display control register at 0x88B0 with 0x010F
#Sets r5 to 0x0F
#Affects no other registers
#2017-11-02
init:
	ori sp,r0,stacktop 			# initializes stack pointer
	push r3
	push r4
	push ra
	ori r3,r0, 0x88B0 			# r3 is address of hex control register
	ori r4, r0, 0x010F 			# Control code to turn first four hex on
	sthio r4, (r3) 			# Sends control code to hex control register
	ori r5, r0, 0x0F 			# Set r5 equal to 0x0F
	pop ra
	pop r4
	pop r3
	ret

#Shanece Wilson
#Matthew Sampson
#Delays for 10*N microseconds, up to 10 seconds
#Affects no registers
#Uses decarde timmer at address 0x8870
#2017-11-02
delay:
	push r3
	push r4
	push r5
	push r6
	push r7
	push r8
	ori r8, r0, N 				# Sets r8 to N
	orhi r7, r0, 0x000F 			# Sets r7 to a million (1 milllion * 10 microseconds = 10seconds)
	ori r7,r7, 0x4240
	ori r6, r0, 0 				# Sets r6 to 0
	ori r5, r0, 0x01 			# Sets r5 to 0b00000001
	ori r3, r0, 0x8870 			# r3 = address decade timer
delay_waitLow:
	ldbio r4, (r3) 			# R4 equals value of decade timer
	andi r4, r4, 0x01 			# Looks only at last bit of r4
	bne r4, r0, delay_waitLow
delay_waitHigh:
	ldbio r4, (r3)
	andi r4, r4, 0x01
	bne r4, r5, delay_waitHigh
	addi r6, r6, 1
	beq r6, r7, delay_over
	bne r6, r8, delay_waitLow
delay_over:
	pop r8
	pop r7
	pop r6
	pop r5
	pop r4
	pop r3
	ret

#Authors: Tristen Tulkens, Jacob Smith
#Date: November 3, 2017
#Purpose: Waits for switch 0 to go up and down
#Registers Affected: None
#Passed Values: 0

switch0:

	push r5
	push r6

	ori r5,r0,0x8850			# r5 = addr of switches

switchtop:

	ldwio r6,0(r5) 			# r6 = value of switches
	andi r6, r6, 1 			# isolate switch 0

	bne r6, r0, switchtop 		# if r6 ~= r0 go to switchtop

switchmid:

	ldwio r6, 0(r5) 			# r6 = value of switches
	andi r6, r6, 1 			# isolate switch 0

	beq r6, r0, switchmid 		# if r6 = 0 go to switch mid

	pop r6
	pop r5
	ret

#-----------------------------------------------
# DATE: Nov 02nd 2017 NAME: T.Ryan, E.Henderson
# This subroutine will read the four blue buttons and if any button is found pressed, set the
# corresponding bit to zero in r5. No registers except r5 are affected. Will only work if one
# button is pressed
#-----------------------------------------------
buttons:

	push r6
	push r7
	push r16

	ori r16,r0,0x8860 			# r16 = button address
	ldhio r6,(r16) 			# load current presses into r6
	andi r6,r6,0xF				# Mask all other bits to 0

	and r5, r5, r6				# Change any bits that changed to 0


	pop r16
	pop r7
	pop r6

	ret

# INCX */

#Authors: Sage McConnell and Alexandre Walsh
#Date: November 2, 2017
#Description: Increments the value stored in memory location referenced in r22
#No registers are affected by this subroutine
incx:
	push r2
	push r3

	ldb r2,(r22) 				# Load byte from memory location in r22
	addi r2,r2,1 				# Increment loaded value
	ori r3,r0,0x10 			# Initialize comparison value
	bne r2,r3,incx_skip 			# Check if 4 bits are exceeded
	ori r2,r0,0 				# Reset loaded value
incx_skip:
	stb r2, (r22) 				# Store byte back in memory location

	pop r3
	pop r2
	ret

# END INCX */

#/* Author: Koceila Cherfouh, Colton Rossiter
#Date: Nov 2, 2017
#Purpose: Reset code: values to 0
#Register Affected: None
reset4:

	push r4 				# push r4
	ori r4,r0,code 			# r4= address of the memory location code
	stw r0, 0(r4) 				# store 0 at the address code:
	pop r4 					# Pop r4

	ret

#/*------------------------------------------------
#Name: show4
#Author: Emma Landry and Alex Roberts
#Date: Nov 2, 2017
#Purpose: This subroutine displays the four stored digits in the hex display
#Registers Affected: None
#Values Passed To/From: None
#------------------------------------------------*/

show4:
	push r6
	push r5 				# Store r5
	push r3 				# store r3
	push r4 				# store r4
	push ra 				# store ra

	ori r5 ,r0, code 			# r5 = code
	ori r4,r0,0x88A0 			# r4 = address of hex
	ldb r3,3(r5) 				# load the first digit
	slli r3,r3,4
	ldb r6, 2(r5)				# load the second digit
	or r3,r3,r6
	slli r3,r3,4
	ldb r6, 1(r5)				# load the third digit
	or r3,r3,r6
	slli r3,r3,4
	ldb r6, 0(r5)				# load the fourth digit
	or r3,r3,r6

	stwio r3, (r4) 			# send word to Hex7 +

	pop ra 					# restore ra
	pop r4 					# restore r4
	pop r3 					# restore r3
	pop r5 					# restore r5
	pop r6
	ret

# END SHOW4


# CHECK4 */
# Mike Walz and Mackenzie Toner

check4:
	push r4
	push r5

	or r5,r0,r0 				# set r5 to 0
	ldbu r4,0(r22) 			# load first hex value at 0r22
	andi r4,r4,0x0F 			# mask last 4 bits of r4

	ldbu r5,1(r22) 			# load second hex value at 1r22
	andi r5,r5,0x0F 			# mask last 4 bits of r5
	bne r4,r5,checkEnd 			# check if bits are equal

	ldbu r5,2(r22) 			# load third hex value at 1r22
	andi r5,r5,0x0F 			# mask last 4 bits of r5
	bne r4,r5,checkEnd 			# check if bits are equal

	ldbu r5,3(r22) 			# load fourth hex value at 1r22
	andi r5,r5,0x0F 			# mask last 4 bits of r5
	bne r4,r5,checkEnd 			# check if bits are equal

	push ra
	call fireworks 			# yay
	pop ra

checkEnd:
	pop r5
	pop r4

	ret

# END CHECK4 */

#Shanece Wilson
#Matthew Sampson
#Sends r3 to hex display, address 0x88A0
#No registers affected
#Uses r3, required hex to be turned on
#2017-11-02
outhex:
	push r5
	ori r5, r0, 0x88A0 			# r5 is address of hex display
	orhi r3, r3, 0x0000 			# Makes sure 16 MSB of r3 are 0.. not super important
	stwio r3, (r5) 			# Sends r3 to hex display
	pop r5
	ret

#Shanece Wilson
#Matthew Sampson
#Sends r3 to LEDs at 0x8880
#No registers affected
#2017-11-2
outled:
	push r5
	ori r5, r0, 0x8880 			# r5 is LED address
	sthio r3, (r5) 			# sends r3 to LED
	pop r5
	ret

#Patrick Walsh
#Weston Wood
#Sets code to 0,0,0,0
#Affects no other registers
#2017-11-02
fireworks:
push r6
push r7
push r4
push r5
push ra
ori r6,r0,0x8880 				# r6 is the address of the LEDs
ori r7,r0,10 					# r7 = repeat counter

x3:
ori r4,r0,0xAAAA 				# sets every second LED
stwio r4,(r6) 					# turn on LEDs

ori r3,r0,65000 				# for 1/10th of a second
call delay
call delay

ori r5,r0,0x5555 				# sets every LED left
stwio r5,(r6) 					# turn on LEDs
call delay
call delay

addi r7,r7,-1 					# decriment counter
bne r7,r0,x3 					# repeat

stwio r0,(r6) 					# turn on LEDs
pop ra
pop r5
pop r4
pop r7
pop r6
ret

#-------------------------------------------------------------------
code: .byte 3,2,0,1 			# store the four display digits here
#-------------------------------------------------------------------
	.skip 200 					# stack = 200 bytes = 50 words
stacktop: 						# end of stack space allocation
#-------------------------------------------------------------------
.end
