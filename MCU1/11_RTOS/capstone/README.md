# RTOS Capstone — Multi-Task Sensor and Diagnostic System

**Status:** Planned.

Build a small RTOS-based firmware system that combines periodic sensing, UART diagnostics, and event-driven control.

## Suggested tasks
- Sensor/acquisition task
- UART/CLI task
- LED/status task
- health-monitor task

## Key concepts
- task scheduling
- priorities
- queues
- mutexes/semaphores
- ISR-to-task communication
- stack sizing
- priority inversion
- timing and responsiveness

## Acceptance
Tasks communicate through explicit RTOS primitives and interrupt work remains short and deterministic.