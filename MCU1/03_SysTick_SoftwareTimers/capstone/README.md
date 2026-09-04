# SysTick / Software Timer Capstone — Non-Blocking LED Scheduler

**Status:** Completed and hardware-tested.

Use SysTick as a 1 ms time base and build a small software-timer service that schedules LED patterns and button debounce without busy-wait delays.

## Key concepts
- SysTick configuration
- millisecond time base
- elapsed-time comparison
- non-blocking scheduling
- multiple software timers
- debounce timing
- state-machine integration

## Acceptance
LED patterns and debounce continue to operate while the CPU remains available for other application work.