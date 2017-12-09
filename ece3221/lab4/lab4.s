# ECE3221 LAB#4 - Interrupts
# -----------------------------------------------
# DATE: Nov 2017 NAME: Jacob Smith & Tristen Tulkens
# -----------------------------------------------

# A Timer
# -----------------------------------------------

.global _start

# Macros
# ==========================================
.macro push rx
	addi sp ,sp ,-4
	stw \rx ,0(sp)
.endm

.macro pop rx
	ldw \rx ,0(sp)
	addi sp ,sp ,4
.endm

# Variables
# ==========================================
.equ hexcontrolreg,0x000088B0
.equ hex,0x000088A0
.equ timer,0x00008870
.equ max,0x9599
.equ leds,0x00008880
.equ lcd,0x88C0
.equ N,100

# Interupt Service Routine
# ==========================================
	.org 0x0020 # this code lies at address 20
	push r3
	push r4
	push r6
	push r10
	push ra
	
	# determine source of interrupt
	# ------------------------------------
	# was it the timer input port?
	
	rdctl r3,ipending 		# r3 = pending interrupt bits
	andi r4,r3,0b00000100 	# r3 = pending int2 bit
	beq r4,r0,endint 		# ignore if not int2
	
	ori r10,r0,leds			# r10 = Address of LEDs
	ldhio r6,(r10)			# r6 = Value of LEDs
	srli r6,r6,1			# Shift bit left
	bne r6,r0,aa			# Branch if bit not off right side
	ori r6,r0,0x200			# Set bit 9 high
aa:	sthio r6,(r10)			# Load value to LEDs
	
	# write (clear) timer edge detection
	ori r4,r0,timer
	stwio r3,12(r4) # clear int
	
	call clocker
	call show4
	
endint:
	pop ra
	pop r10
	pop r6
	pop r4
	pop r3
	addi ea,ea,-4 # ISR done
	eret


# Main Program
# ==========================================
_start:
	call init			# Intialize the program
	call initlcd
	
	ori r8,r0,hex       # Load address of hex
	ori r10,r0,time     # Load address of time	

here:
    ldwio r3,(r10)		# Load value in time
	nop
	nop
	nop
	nop
	stwio r3,(r8)		# Send value in time to hex display
	nop
	nop
	nop
	nop
	
    br here             # Loop forever


# Subroutines
# ==========================================

# Init
# Purpose: Init stack pointer, enable all interrupt stuff, activate hex display
# Registers Affected: None
# Parameters: None
# Retuns: None
init:
	ori sp,r0,stacktop # set stack pointer
	
	push r3
	push r5
	push r6
	push r22
	
	# enable four hex digits
	ori r6,r0,0x010F
	ori r5,r0,hexcontrolreg
	sthio r6,(r5)
	
	# SETUP INTERRUPTS IN THREE STEPS 1,2,3
	# (1) enable timer interrupt on 10 Hz edge
	ori r22,r0,timer		# Load address of timer
	ori r3,r0,0b00010000 	# select 10 Hz output
	stbio r3,8(r22)			# Write selection timer interrupt mask
	
	# (2) enable int2 (decade timer) in processor
	rdctl r3,ienable		# Load address of processor interrupt mask
	ori r3,r3,0b0100		# int2 = bit 2 = 1
	wrctl ienable,r3		# Write to processor interrupt mask
	
	# (3) turn on master interrupt enable
	rdctl r3,status			# Load device interrupt mask
	ori r3,r3,0x01 			# PIE bit = 1
	wrctl status ,r3		# Write to device interrupt mask
	
	pop r22
	pop r6
	pop r5
	pop r3
	
	ret

# Init LCD
# ==========================================

# Init LCD
# Purpose: Init LCD
# Registers Affected: None
# Parameters: None
# Retuns: None
initlcd:
	push ra
	push r3

	# Init LCD
	ori r3,r0,0x101
	call outchr
	ori r3,r0,0x102
	call outchr
	
	ori r3,r0,mystring
	call outstr
	
	ori r3,r0,0x1c4		# Command to go to address of minute value
	call outchr
	
	ori r3,r0,initstr
	call outstr
	
	pop r3
	pop ra
	ret
	
# Clocker
# Purpose: Increment the four digit BCD time stored in the label time
# Registers Affected: None
# Parameters: None
# Retuns: None
clocker:
	push r3
	push r4
	push r8
	push r22
	
	ori r22,r0,time		# Load address of time
	
	ldw r3,(r22)		# Load value in time
	ori r8,r0,max		# Load max value of time
	beq r3,r8,done	    # Do not update if time == max
	
	ldh r3,0(r22)		# Load value of time
	addi r3,r3,1		# Add one to time value
	andi r4,r3,0x000F      # Mask first byte
	ori r8,r0,0xA		# Load A into r8
	bne r4,r8,done		# Done if r4 != 10
	
	addi r3,r3,-10		# Set first byte to 0
	addi r3,r3,0x10		# Increment seconds spot
	andi r4,r3,0x00F0 	# Mask seconds spot
	ori r8,r0,0xA0		# Load A into r8
	bne r4,r8,done

	addi r3,r3,-0xA0	# Reset seconds
	addi r3,r3,0x100	# Increment decasecond
	ori r8,r0,0x0600
	andi r4,r3,0x0F00	# Mask decaseconds spot
	bne r4,r8,done
	
	addi r3,r3,-0x0600	# Reset decasecond
	addi r3,r3,0x1000	# Increment minute
	

done:
	sth r3,(r22)
	pop r22
	pop r8
	pop r4
	pop r3
	
	ret
	
# Delay
# Purpose: Delay the program for a specified amount of time
# Registers Affected: None
# Parameters: r5: number of rising edges with 0.1ms interval
# Retuns: None
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
	ldbio r4, (r3) 				# R4 equals value of decade timer
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


# Outchr
# Purpose: Send single value in r3 to LCD
# Registers Affected: None
# Parameters: r3: value to send to LCD
# Retuns: None
outchr:
	push ra
	push r4
	push r5
	push r10
	
	ori r10,r0,lcd 		# Load address of LCD
	
	or r4,r0,r3			# Send input to r4
	
	ori r4,r4,0x600		# Set bit 9 to 1
	stwio r4,(r10)		# Send high value to lcd
	
	call delay			# Delay 1ms
	
	andi r4,r4,0xFDFF	# Set bit 9 to 0
	stwio r4,(r10)		# Send low value lcd
	
	
	pop r10
	pop r5
	pop r4
	pop ra
	ret

# Outstr
# Purpose: Send a string to the LCD
# Registers Affected: None
# Parameters: r3: address of string
# Retuns: None
outstr:
	push ra
	push r4
	or r4,r0,r3
	push r3
	
loop:
	and r3,r3,r0
	ldb r3,0(r4)		# Load character of input string
	beq r3,r0,finished
	call outchr
	addi r4,r4,1		# Increment address
	br loop
	
finished:
	pop r3
	pop r4
	pop ra
	ret
	
# show4
# Purpose: Send a string to the LCD
# Registers Affected: None
# Parameters: None
# Retuns: None
show4:
	push ra
	push r2
	push r3
	push r8
	
	ori r8,r0,time		# Load address of time
	ldh r2,(r8)			# Load value of time
	
	ori r3,r0,0x1CA
	call outchr
	andi r3,r2,0xF
	addi r3,r3,'0'
	call outchr
	
	srli r2,r2,4
	ori r3,r0,0x1C8
	call outchr
	andi r3,r2,0xF
	addi r3,r3,'0'
	call outchr
	
	srli r2,r2,4
	ori r3,r0,0x1C7
	call outchr
	andi r3,r2,0xF
	addi r3,r3,'0'
	call outchr
	
	srli r2,r2,4
	ori r3,r0,0x1C4
	call outchr
	andi r3,r2,0xF
	addi r3,r3,'0'
	call outchr
	
	pop r8
	pop r3
	pop r2
	pop ra
	ret
	
# Data Storage
# ==========================================

# reserve 400 bytes = 100 words for stack
.skip 400
stacktop:

# ------------------------------------------
# four digits for the time stored in BCD format
time: .byte 0,0,0,0

pattern: .word 0 # display LED state

# string to be displayed on Line 1
# may be modified (maximum 16 characters)
mystring: .asciz "TIME SINCE START"
initstr:  .asciz "0m 00.0s"

.end
