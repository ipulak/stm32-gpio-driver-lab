# Timer 02 — TIM2 Polling

## Objective
Use TIM2 as a hardware time base and observe its update/event status using polling.

## Configuration
- MCU: STM32F407VG
- Timer: TIM2
- Timer clock: 16 MHz
- PSC: 15
- ARR: 999
- Counter frequency: 1 MHz
- Tick: 1 us
- Update period: 1 ms

## Concepts
- Status register (SR)
- Update interrupt flag (UIF)
- Polling versus interrupt-driven execution
- Clearing timer status flags

## CPU behavior
The CPU repeatedly checks the timer status. This is simple but consumes CPU cycles while waiting.

## Next stage
`timer_03_interrupt` replaces polling with a TIM2 interrupt.
