# Timer 01 — Basic TIM2 Counter

## Objective
Configure STM32F407 TIM2 as a basic free-running hardware timer.

## Configuration
- MCU: STM32F407VG
- Timer: TIM2
- Timer clock: 16 MHz
- PSC: 15
- ARR: 999
- Counter frequency: 1 MHz
- Timer tick: 1 us
- Update period: 1 ms

## Concepts
- APB1 timer clock
- Prescaler (PSC)
- Auto-reload register (ARR)
- Counter register (CNT)
- Free-running timer

## Learning outcome
This is the baseline hardware-timer project used to understand how TIM2 counts independently of the CPU.

## Next stage
`timer_02_polling` adds software observation of the timer update condition.
