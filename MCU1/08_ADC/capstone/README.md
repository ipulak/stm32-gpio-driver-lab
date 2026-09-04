# ADC Capstone — Timer-Triggered Data Acquisition

**Status:** Planned.

Use a hardware timer to trigger ADC conversions at a deterministic sample rate. Store samples in memory and expose basic statistics through UART.

## Key concepts
- ADC configuration and conversion
- sample time
- timer-triggered conversion
- end-of-conversion status
- sampling frequency
- fixed-size data buffers

## Acceptance
Acquire a repeatable stream of samples at a defined rate and calculate basic statistics without blocking the application.