# SysTick & Software Timers — MCU1

This directory contains the complete progression developed on the STM32F407 Discovery board.

## Projects

| Stage | Project | Main concept |
|---|---|---|
| 01 | `timer_01_basic` | TIM2 free-running counter |
| 02 | `timer_02_polling` | Timer status polling |
| 03 | `timer_03_interrupt` | TIM2 update interrupt + NVIC |
| 04 | `timer_04_systick` | Cortex-M SysTick |
| 05 | `timer_05_systick_1ms` | 1 ms system time base |
| 06 | `timer_06_capstone` | Software timer framework |

## Learning progression

```text
TIM2 counter
   ↓
Polling
   ↓
TIM2 interrupt
   ↓
SysTick
   ↓
1 ms system tick
   ↓
Software timers
   ↓
Button debounce + LED pattern + state-machine application
```

## Timer calculations
For the TIM2 projects:

`Timer counter frequency = Timer clock / (PSC + 1)`

With a 16 MHz timer clock and `PSC = 15`:

`16 MHz / 16 = 1 MHz` → 1 us per counter tick.

With `ARR = 999`, the update period is:

`(999 + 1) × 1 us = 1 ms`.

## Key interview distinction
TIM2 is a general-purpose hardware peripheral timer. SysTick is part of the Cortex-M core and is commonly used as a system time base. Software timers can then be layered above the regular tick.

See `tim2_interrupt_architecture.md` for the interrupt architecture notes.
