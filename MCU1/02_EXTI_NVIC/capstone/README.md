# EXTI/NVIC Capstone — Interrupt-Driven Event Controller

**Status:** Planned / to be consolidated from the GPIO interrupt work.

Implement a clean interrupt path for the STM32F407 user button using PA0 → EXTI0 → NVIC → ISR. The ISR records an event; application logic handles the event outside interrupt context.

## Key concepts
- SYSCFG EXTICR routing
- EXTI pending flag
- rising/falling edge configuration
- NVIC enable/priority
- ISR design and minimal interrupt work
- ISR-to-main event handoff

## Acceptance
A button press produces exactly one application event per valid press, with no long-running work inside the ISR.