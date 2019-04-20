// Questions:
// 1. What does the COCO bit stand for?
// 2. What does ADCH stand for?
// 3. Which register is the above to items located?
// 4. What does DAC0_C0 |= 0xC0 do?

// Steps:
// 1. GPIO has 3 steps
// 2. ADC has 4 steps
// 3. UART has 7 steps
// 4. DAC has 4 steps
// 4. FTM has 4 steps

void uart_init() {
	SIM_SCGC6 |= SIM_SCGC6_UART_MASK;
	SIM_SCGC5 |= SIM_SCGC6_PORTB_MASK | SIM_SCGC6_PORTE_MASK;

	PORTB_PCR15 = PORT_PCR_MUX(3);
	PORTE_PCR18 = PORT_PCR_MUX(3);

 	UART0_C2 &= ~(UART_C2_RE_MASK | UART_C2_TE_MASK);
    
    	// turn off parity & set data bits to 8
    	UART0_C1 |= 0b10;

    	// set baud rate to 9600
    	UART0_BDL = 0;
    	UART0_BDH = 0x88;

    	UART0_C2 |= UART_C2_RE_MASK | UART_C2_TE_MASK;
}

void uart_put_char(char c) {
    	while (!(UART0_S1 & UART_S1_TDRE_MASK)) {}
    	UART0_D = c;
}

char uart_get_char() {
    	while (!(UART0_S1 & UART_S1_RDRF)) {}
    	return UART0_D;
}

void adc_init() {
    	// TURN ON the clocks
   	SIM_SCGC4 |= SIM_SCGC4_ADC0_MASK;
	SIM_SCGC6 |= SIM_SCGC6_PORTE_MASK;
}

double adc_read() {
	ADC0_SC1A |= ADC_SC1A_ADCH(17); // we are using ADC0_SE17
	while (!(ADC0_SC1A & ADC_SC1A_COCO_MASK));
	RETURN ((double)ADC0_RA) / pow(2, 12) * 3.3;
}

void dac_init() {
	// turn on the clock
    	SIM_SCGC7 |= SIM_SCGC7_DAC0;
	SIM_SCGC5 |= SIM_SCGC5_PORTE;

	DAC0_C0 |= 0xC0;
}

void dac_write(double value) {
	short val = value * 3.3 / pow(2, 12);
	DAC0_DATOL |= val & 0xFF;
	DAC0_DATOH |= (val >> 8) & 0xF;
}

void gpio_init() {
    	SIM_SCGC5 |= SIM_SCGC6_PORTC_MASK;
	
	PORTC_PCR10 = PORT_PCR_MUX(3);
	PORTC_PCR11 = PORT_PCR_MUX(3);
	
	// make 11 an input and 10 and output
	GPIOC_PDDR &= ~(1 << 10);
	GPIOC_PDDR |= 1 << 11;
}

short gpio_read() {
    return (GPIOC_PDIR >> 10) & 1;
}

void gpio_write(short value) {
    	GPIOC_PSOR |= (value & 1) << 11;
	GPIOC_PCOR |= ((value & 1) ^ 1) << 11;
}

void ftm_init() {
    	// Init the clock
	SIM_SCGC6 |= SIM_SCGC6_FTM0_MASK;

	// Disable write protection
	FTM0_MODE |= FTM_MODE_WPDIS_MASK;

	// Turn on the system clock
	FTM0_SC |= FTM_SC_CLKS(1);
	
	// set the mod
	FTM0_MOD = 0xFFFF;

}

void ftm_delay(double seconds) {
    	int n = seconds * FREQ;
	int count = 0;

	// Reset overflow
	FTM0_SC &= ~FTM_SC_TOF_MASK;

	// Writing any value resets the timer
	// Reset count to 0
	FTM0_CNT = 0;

	while(count + FTM0_CNT < n) {
		if (FTM0_SC & FTM_SC_TOF_MASK) {
			count += MODO;
			// Writing 0 to TOF to clear bit
			FTM0_SC &= ~FTM_SC_TOF_MASK;
		}
	}

	uart_print("Done delaying.\n\r");

}



// // // // // // // // // // // // // // // // // // // //
// // // // // // // // // // // // // // // // // // // //
// // // // // // // // // // // // // // // // // // // //

//
// MIN ADC
//

double read() {
	ADC0_SC1A &= 17;
	while (!(ADC0_SC1A & ADC_SC1_COCO_MASK)) {}
	return ((double) ADC0_RA) * 3.3 / pow(2, 10);
}

int main(void) {
	SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;
	SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;
	
	PORTE_PCR26 |= PORT_PCR_MUX(1);
	
	ADC0_CFG1 |= 0b0101000;

	while (1) {
		double result = read();
	}
}

//
// MIN GPIO
//

void GPIO_init(){
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK;

	PORTC_PCR6 |= PORT_PCR_MUX(1); // SWITCH
	PORTB_PCR21 |= PORT_PCR_MUX(1);  // LED
	PORTB_PCR22 |= PORT_PCR_MUX(1);  // LED

	GPIOC_PDDR &= ~(1 << 6);
	GPIOB_PDDR |= 1 << 21;
	GPIOB_PDDR |= 1 << 22;
}

void GPIO_go() {
	while (1) {
		int input = (GPIOC_PDIR >> 6) & 1;
		GPIOB_PSOR = input << 21;
		GPIOB_PCOR = (input ^ 1) << 21;
		GPIOB_PSOR = input << 22;
		GPIOB_PCOR = (input ^ 1) << 22;
	}
}

int main() {
	GPIO_init();
	GPIO_go();
}

//
// MIN UART
//

void initUART0() {
	// Enable the CLOCK
	SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;

	// Enable UART0_RX and UART0_TX
	PORTB_PCR16 |= PORT_PCR_MUX(3);
	PORTB_PCR17 |= PORT_PCR_MUX(3);

	// Set the BAUD RATE to 9600
	UART0_BDL = 0x88;

	UART0_C2 |= UART_C2_TE_MASK | UART_C2_RE_MASK;
}

char readChar() {
	while(!(UART0_S1 & UART_S1_RDRF_MASK)) {}
	return UART0_D;
}

void writeChar(char c) {
	while(!(UART0_S1 & UART_S1_TDRE_MASK)) {}
	UART0_D = c;
}

void write(char* string) {
	while (*string) {
		writeChar(*string);
		string++;
	}
}

int main(void) {
	initUART0();
	writeChar('h');
	write("HELLO WORLD");

	while (1) {
		writeChar(readChar());
	}

    return 0;
}