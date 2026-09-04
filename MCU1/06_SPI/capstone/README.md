# SPI Capstone — Register-Level Peripheral Interface

**Status:** Planned.

Implement an SPI master driver at register level and connect a practical peripheral such as an external sensor, display, or memory device.

## Key concepts
- SPI clock/prescaler
- CPOL/CPHA
- full-duplex transfer
- TXE / RXNE / BSY
- chip-select handling
- interrupt and DMA extensions

## Acceptance
Read a known device register reliably and expose the result through the UART diagnostic console.