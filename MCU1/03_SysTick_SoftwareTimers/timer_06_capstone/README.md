# Timer 06 — Software Timer Capstone

## Objective
Build a small bare-metal timing framework on STM32F407 using SysTick as a 1 ms time base.

## Features
- SysTick 1 ms time base
- Multiple software timers
- LED pattern timing
- Button debounce timing
- Event-driven application behavior
- Simple state-machine style application flow

## Architecture
```text
SysTick ISR
    ↓
1 ms time base
    ↓
Software timer manager
    ├── LED pattern timer
    ├── button debounce timer
    └── application timers
    ↓
Application/state machine
```

## Design goal
Keep the ISR short and deterministic. Time measurement belongs to the time-base/timer layer; application behavior belongs to the main loop.

## Interview focus
Explain why a hardware timer/SysTick time base is preferable to busy-wait delays, how software timers scale, and how ISR/main-loop ownership is kept safe.
