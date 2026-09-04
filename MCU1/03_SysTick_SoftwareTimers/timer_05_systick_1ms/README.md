# Timer 05 — SysTick 1 ms Time Base

## Objective
Build a deterministic 1 ms system time base using Cortex-M SysTick and use that tick for software timing.

## Concepts
- 1 ms SysTick configuration
- Millisecond counter
- Software timer expiry
- Periodic versus one-shot timing
- Separating time-base generation from application logic

## Architecture
SysTick ISR → 1 ms tick → software timers → application events.

## Why it matters
The CPU is interrupted only once per millisecond; application code can check timer state without busy-waiting for every delay.

## Next stage
`timer_06_capstone` combines the time base, software timers, button debounce and LED-pattern state-machine behavior.
