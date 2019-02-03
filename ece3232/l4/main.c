#include <math.h>
#include "fsl_device_registers.h"
#include "console.h"

static int i = 0;

// PTE24 ADC0_SE17

void ADCx_Init() {
	// Enable clock to ADC0
	SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;

	// Enable port E
	SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;

	// 01 input_clock / 2, 0 short time sample, 10 since DIFF == 0, 00 clock_source = bus clock
	ADC0_CFG1 |= 0b0101000;

	// 0 ADxxa channel select, 0 normal conversion sequence
	ADC0_CFG2 |= 0b00;

	// 5. Select software/hardware trigger, DMA, Compare, voltage reference, continuous conversons
	ADC0_SC2 |= 0b00000;

	// do not start calibration, one conversion
	// ADCx_SC3 |= 0b00;
	// 6. Select ADC0_SE17
	ADC0_SC1A &= 0x11;
}

double ADCx_Convert() {
	ADC0_SC1A |= ADC_SC1_ADCH(17);

	while(!(ADC0_SC1A & 0b10000000)) {}

	return (double)ADC0_RA / pow(2, 10) * 3.3;
}

int main(void) {
	double val;

	ADCx_Init();

	while(1) {
		val = ADCx_Convert();
	}

    return 0;
}
