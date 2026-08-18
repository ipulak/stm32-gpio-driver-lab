# Project 01B — STM32 GPIO Fault Injection & Debugging

A hands-on STM32F407 GPIO debugging laboratory focused on
fault injection, register inspection, fault isolation, and
root-cause analysis.

This project builds on Project 01, where PD13 was configured as
a GPIO output to control the LD3 orange LED on the STM32F4DISCOVERY
board.

Instead of only demonstrating a working GPIO implementation,
this project deliberately introduces firmware faults and uses
the STM32CubeIDE debugger to identify and resolve them.

---

## Objectives

The primary objective is to develop a systematic embedded
firmware debugging methodology.

This project focuses on:

- Peripheral clock debugging
- GPIO register inspection
- GPIO pin configuration analysis
- Memory-mapped register debugging
- Bit-position analysis
- Pin mapping verification
- Fault isolation
- Root-cause analysis
- Debugger-based verification
- Hardware/software correlation

---

## Hardware

| Item | Details |
|---|---|
| Development Board | STM32F4DISCOVERY |
| MCU | STM32F407VGT6 |
| CPU | ARM Cortex-M4 |
| Debugger | On-board ST-LINK |
| LED | LD3 Orange |
| Expected GPIO | PD13 |
| IDE | STM32CubeIDE |

---

# Debugging Philosophy

The project follows a structured debugging process:

```text
                 Symptom
                    |
                    v
              Form hypothesis
                    |
                    v
             Inspect registers
                    |
                    v
               Verify state
                    |
                    v
              Isolate fault
                    |
                    v
              Identify root cause
                    |
                    v
                  Fix
                    |
                    v
              Verify hardware
