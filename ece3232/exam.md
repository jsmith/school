# Exam
Module Lecture
https://lms.unb.ca/d2l/le/content/148767/viewContent/1536431/View

## Introduction
- Cross compiled & linked
- Downloaded to target
- Connected via USB
- Can run standalone
- ARM 120 MHz Cortex-M4 Processor, M meaning microcontrollers
- “Modified” Harvard bus architecture w/ simultaneous instruction & data access, 3-stage pipeline
- Eclipse based IDE
- Board support package
- FRDM-K64F
- gcc – compiler, linker, assembler
- make – controls generation of executables

## CPU Cortex M4
- software flow is compiler -> assembler -> linker
- Linker is the process of assigning memory to all global objects
- `Section` is a group of global objects declared in a source file
- `Segment` is a memory range
- There is a linker parameter file
- Sections are associated with segments

### Analog I/O
- 2 16 bit SAR ADCs 1.2 MS/s in 12 bit mode
- 2 12 bit DACs
- 3 analog comparators with 6 bit DAC

### Communication
- Ethernet
- CAN
- 6 UART, 1 low power
- 3 I2C
- Others (USB OTG, I2S, 3 SPI)

### HMI
- Up to 81 GPIO

### Timers
- LOTS

### FRDM-K64F Modules
- Crossbar switch lite (AXBS): Allows different masters to access different slaves
- Peripheral bridge (AIPS-Lite): Converts the crossbar switch interface to an interface that can access most slaves/peripherals
- System integration module (SIM): Registers for system control and chip, system clocking configuration
- FlexBus: Multi-functional external bus interface controller, connection peripherals via external bus
- PORT: One port module for each 32-bit port, A/B/C/D/E, interrupt for each pin, filtering, port control (pull up/down, drive strength, filter enable, etc)
- Port memory map: Pin control register for each bit, global pin control high/low registers, interrupt status flag register, some other weird filter registers
- Signal multiprocessing: Port control block controls which signal is present on each external pin, not all of the pins are available on the device
- General purpose input/output: Set using port data direction register, controlled using the port data input/output registers, clocked with system clock, can do 8/16/32 bits

Each module is controlled using a set of registers that are mapped into the memory space of the board.

## Serial
- Serial vs. parallel
- Synchronous vs. asynchronous
- parallel has multiple data lines, needs control signals, usually shorter distances, faster
- serial uses multiple bits per data line, longer distances, slower, asynchronous and synchronous
- Performance measues include error rate, latency, bandwidth, level of security
- baud rate is the symbol or modulation rate, units are symbols per second, if 1 bit per symbol -> baud = bit rate, if 2 bits per symbol -> baud rate = bit rate / 2, vice versa

### Requirements
- medium
- transmitter/receiver
- data
- protocol: synchronization (clocks, handshaking, error checking), data packaging (data, control bits)

### Hardware (copied)
– UART – universal asynchronous
receiver/transmitter (SCI or ACIA – asynchronous
communications interface adapter)
– SPI – synchronous peripheral interface
– I2C – two wire bidirectional
– I2S –synchronous audio interface, full duplex
– USB – universal serial bus

Baud Rate = UART module clock / (16 * SBR[12:0] + BFRD)

## ADC Basics
- Most ADCs have a reference voltage, a switching network of Rs and Cs, and an op amp
- Precision – number of distinguishable inputs, quanta
- Input Range – max and min ADC input (volts or amps)
- Resolution – smallest distinguishable change in input ( volts, amps)
- Range(volts) =precision(alternatives) *
resolution(volts)
- ADC is monotonic if no missing codes, linear if resolution constant through range
- Unipolar - binary, complementary binary
- Bipolar – offset binary, 2s complement

## FRDM K64 ADC
- Differential inputs -> A signal input circuit where Signal LO and Signal HI are electrically floating with respect to ANALOG ground
- Single ended inputs -> One low wire shared by all inputs

## System Design
Use these lectures!! Info about the design process and the diagrams...

https://lms.unb.ca/d2l/le/content/148767/viewContent/1548092/View
https://lms.unb.ca/d2l/le/content/148767/viewContent/1549757/View

## Sensors & Actuators
– Transduction - Change in measured physical variable
(pressure, temperature, displacement) is translated
into a change in property ( resistance, capacitance,
magnetic coupling) of the transducer
– Transducer is a device that converts energy from one
form to another.
– Sensors: receive and respond to a signal or stimulus
from a physical system. Change in the property of the
transducer is translated into a low-power-level
electrical signal in the form of voltage or current
– The low-power sensor signal is amplified, conditioned
and transmitted to an intelligent device for processing
– Actuators: move or control a mechanism. Operated by
a source of energy (mechanical force, electrical
current, hydralic fluid pressure or pneumatic
pressure) and converts that energy into motion
– The actuator is controlled by a signal from a control
system or manual control
– Bidirectional transducers

See https://lms.unb.ca/d2l/le/content/148767/viewContent/1550993/View for a complete list of sensors.

## Detailed Design & Testing
https://lms.unb.ca/d2l/le/content/148767/viewContent/1555914/View

### Electrical Characteristics
• VOH – lowest guaranteed output voltage for a
logic high
• VOL – highest guaranteed output voltage for a
logic low
• IOH – max allowable output current for VOH
• IOL – for VOL
• VIH – lowest input voltage guaranteed to be
recognized as a logic high
• VIL – highest input voltage guaranteed to be
recognized as a logic low
• IIH - input current for a VIH logic high
• IIL - current for VIL

• Fanout
– the maximum number of devices that can be
connected to a chip’s pin
– Consider output logic high and output logic
low