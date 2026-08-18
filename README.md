 STM32 GPIO Driver Lab

A hands-on bare-metal embedded firmware laboratory for learning,
implementing, and debugging STM32 GPIO peripherals at the register level.

This repository is being developed on an STM32F4DISCOVERY board and focuses
on understanding the hardware and debugging methodology behind GPIO drivers
rather than relying on STM32 HAL APIs.

---

## Objectives

The objectives of this laboratory are to develop practical skills in:

- STM32 peripheral register programming
- Memory-mapped I/O
- RCC peripheral clock configuration
- GPIO register configuration
- Bit manipulation and register masking
- Hardware-level debugging
- STM32CubeIDE debugging
- Fault isolation and root-cause analysis
- Bare-metal embedded C development
- Reusable embedded driver design

---

## Hardware

| Item | Details |
|---|---|
| Development Board | STM32F4DISCOVERY |
| MCU | STM32F407VGT6 |
| CPU | ARM Cortex-M4 |
| Debugger | On-board ST-LINK |
| LED | LD3 Orange |
| GPIO Pin | PD13 |
| IDE | STM32CubeIDE |

---

# Project 01 — Register-Level GPIO LED

## Objective

Configure GPIO Port D, pin 13 (PD13) as a general-purpose output
and control the LD3 orange user LED on the STM32F4DISCOVERY board.

The implementation directly accesses STM32 memory-mapped registers
without using the STM32 HAL GPIO driver.

---

## Hardware Connection


STM32F407
   |
   +---- PD13
           |
           v
        LD3 Orange LED
