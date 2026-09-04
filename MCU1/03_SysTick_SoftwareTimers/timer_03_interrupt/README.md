# Timer 03 — TIM2 Interrupt

## Objective
Configure TIM2 to generate a periodic update interrupt instead of continuously polling the timer status.

## Concepts
- TIM2 update event
- DIER/UIE
- SR/UIF
- NVIC enable
- `TIM2_IRQHandler()`
- ISR flag handling

## Architecture
TIM2 counts independently → update event sets UIF → NVIC services the interrupt → ISR clears the flag and performs the periodic action.

## Why it matters
This demonstrates the fundamental embedded pattern of replacing CPU polling with event-driven interrupt processing.

## Next stage
`timer_04_systick` introduces Cortex-M SysTick as a separate system time base.
