# Embedded System Design Capstone — Integrated Firmware Platform

**Status:** Final roadmap project.

Combine the strongest pieces from the MCU1 journey into one production-style firmware architecture: drivers, timing, interrupts, communication, acquisition, diagnostics, and RTOS/application layers.

## Architecture
```text
Drivers → BSP → Services → Event/Queue Layer → Application
                  ↑                    ↓
             ISR / DMA             UART CLI
```

## Goals
- clear module boundaries
- static memory where practical
- deterministic timing
- fault handling
- testable interfaces
- logging/diagnostics
- measurable CPU utilization
- architecture documentation

## Acceptance
The system should demonstrate a complete embedded architecture rather than a collection of independent peripheral demos.