# Timer 04 — SysTick

## Objective
Use the Cortex-M SysTick peripheral as a periodic system time base.

## Concepts
- SysTick reload register (RVR)
- Current value register (CVR)
- Control/status register (CSR)
- SysTick interrupt
- `SysTick_Handler()`
- Processor clock as the time-base source

## Architecture
SysTick generates a regular tick → `SysTick_Handler()` runs → the system time base is updated → application timing can be built on top of it.

## Key distinction
TIM2 is a general-purpose peripheral timer. SysTick is a Cortex-M core peripheral intended for a system tick/time base.

## Next stage
`timer_05_systick_1ms` makes the system tick explicitly 1 ms and uses it as the basis for software timing.
