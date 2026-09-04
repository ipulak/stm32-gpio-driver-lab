# GPIO Capstone — Bare-Metal LED & Button Controller

**Status:** Completed and hardware-tested.

Build a reusable register-level GPIO driver around the STM32F407DISCOVERY LEDs and user button. The capstone includes GPIO output, input, bit manipulation, debounce, EXTI/NVIC integration, LED patterns, and a small state machine.

## Deliverables
- GPIO driver (`gpio.c/.h`)
- LED driver (`led.c/.h`)
- interrupt/debounce handling
- LED pattern state machine
- architecture documentation
- interview questions and answers

## Acceptance
Button events must reliably change LED patterns without blocking delays.