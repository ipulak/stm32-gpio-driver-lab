# Hardware Timer Capstone — Timer-Driven PWM and Measurement

**Status:** In progress.

Build a register-level timer application on STM32F407. Start with update-event generation and interrupts, then extend the same project to output compare, PWM, and input capture.

## Key concepts
- APB timer clock
- PSC / ARR / CNT
- update events and UIF
- timer interrupt and NVIC
- CCR/output compare
- PWM duty cycle
- input capture and frequency measurement

## Acceptance
Generate a deterministic periodic event, drive PWM with a configurable duty cycle, and measure an external periodic signal using input capture.