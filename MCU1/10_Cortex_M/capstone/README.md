# Cortex-M Capstone — Fault Diagnostics and Exception Handling

**Status:** Planned.

Build a Cortex-M4 diagnostic module that intentionally exercises and captures common faults, records SCB fault status, and demonstrates exception entry/stacking behavior.

## Key concepts
- exception model
- MSP / PSP
- exception stacking
- NVIC and priorities
- SVC / PendSV concepts
- HardFault / MemManage / BusFault / UsageFault
- SCB fault status registers
- debugger-based fault analysis

## Acceptance
A reproducible fault produces a useful diagnostic record containing the relevant fault status and stacked context.