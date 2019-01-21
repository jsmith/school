// Jacob Smith w/ Michael Walz
// Jacob Student ID -> 3534295
// Janurary 16th, 2019

#include "fsl_device_registers.h"

void Switch_Init() {
	// Mask port for C and port E in the system clock.
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK|SIM_SCGC5_PORTE_MASK;

	// Set Alt 1 for Switch 2 pin and Green LED pin.
	PORTC_PCR6 |= PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK;
	PORTE_PCR26 |= PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK;

	// Set pin for switch-2 to input.
	GPIOC_PDDR &= 0xFFBF;

	// Set pin for green led to output.
	GPIOE_PDDR |= 1 << 26;
}

void Switch_Input() {
	while(1) {
		// Get input from switch (Pin 6), mask input, then shift to LED Pin (Pin 26)
		int masked = (GPIOC_PDIR & (1 << 6)) << 20;

		// SW2 reads 1 when not pressed, so send to PSOR to turn led off.
		GPIOE_PSOR = masked;

		// SW2 reads 0 when pressed, so invert the register and send to PCOR to turn led on.
		GPIOE_PCOR = masked ^ (1 << 26);
	}
}

int main(void) {
	Switch_Init();
	Switch_Input();

	return 0;
}
