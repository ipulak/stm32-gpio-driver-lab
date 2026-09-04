# DMA Capstone — Low-CPU Data Acquisition Pipeline

**Status:** Planned.

Extend the ADC acquisition project with DMA so samples move from peripheral to RAM without CPU intervention for every sample.

## Key concepts
- DMA stream/channel mapping
- peripheral-to-memory transfers
- circular mode
- half-transfer / transfer-complete events
- buffer ownership
- ISR-to-application handoff
- CPU-load comparison with polling

## Acceptance
Maintain continuous acquisition into a ring/circular buffer while the CPU processes completed portions of the buffer.