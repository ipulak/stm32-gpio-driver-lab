# UART Capstone — Interrupt-Driven Diagnostic Console

**Status:** Next major project.

Build a bare-metal UART diagnostic console on STM32F407. Start with polling TX/RX, then move to interrupt-driven reception, a ring buffer, command parsing, and finally DMA where appropriate.

## Example commands
```text
help
led on
led off
pattern 2
timer status
version
```

## Key concepts
- USART register programming
- baud-rate configuration
- TXE / TC / RXNE
- GPIO alternate function
- UART interrupts and NVIC
- ring buffer / producer-consumer design
- command parser
- UART + DMA extension

## Acceptance
The console must receive commands without polling the UART continuously and must remain responsive while LED/timer functions execute.