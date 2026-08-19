# Project 01B — STM32 GPIO Fault Injection & Debugging Lab

## Overview

This project demonstrates a systematic approach to debugging STM32 GPIO
firmware through deliberate fault injection, register inspection,
fault isolation, and root-cause analysis.

The project is based on the STM32F407VGT6 MCU and the STM32F4DISCOVERY
development board.

The objective is to develop practical embedded firmware debugging
skills rather than simply making an LED work.

---

## Objectives

This project focuses on:

- STM32 peripheral clock debugging
- GPIO register-level debugging
- Memory-mapped register analysis
- GPIO pin configuration
- Peripheral base-address verification
- Bit-level analysis
- Hardware/software correlation
- Fault injection
- Fault isolation
- Root-cause analysis
- Debugger-based verification

---

# Hardware

| Item | Details |
|---|---|
| MCU | STM32F407VGT6 |
| CPU | ARM Cortex-M4 |
| Development Board | STM32F4DISCOVERY |
| Debugger | On-board ST-LINK |
| LED | LD3 Orange |
| GPIO Pin | PD13 |
| IDE | STM32CubeIDE |

---

# Known-Good GPIO Configuration

The baseline implementation configures PD13 as a general-purpose
push-pull output and controls the LD3 orange LED.

## 1. Enable GPIOD Clock

```c
RCC_AHB1ENR |= (1U << 3);
```

## 2. Configure PD13 as Output

Each GPIO pin occupies two bits in the MODER register.

For PD13:

```text
Pin number = 13

MODER position = 13 × 2
               = 26

PD13 → MODER[27:26]
```

GPIO mode encoding:

```text
00 → Input
01 → General-purpose output
10 → Alternate function
11 → Analog
```

Configuration:

```c
GPIOD_MODER &= ~(3U << 26);
GPIOD_MODER |=  (1U << 26);
```

## 3. Configure Push-Pull

```c
GPIOD_OTYPER &= ~(1U << 13);
```

## 4. Configure Low-Speed Output

```c
GPIOD_OSPEEDR &= ~(3U << 26);
```

## 5. Disable Pull-Up/Pull-Down

```c
GPIOD_PUPDR &= ~(3U << 26);
```

## 6. Set PD13

```c
GPIOD_BSRR = (1U << 13);
```

This sets PD13.

## 7. Reset PD13

The upper 16 bits of BSRR are used for GPIO reset operations.

For PD13:

```text
Reset bit = Pin number + 16
          = 13 + 16
          = 29
```

Therefore:

```c
GPIOD_BSRR = (1U << 29);
```

---

# Register Map

## RCC

| Register | Address | Purpose |
|---|---:|---|
| RCC_AHB1ENR | `0x40023830` | AHB1 peripheral clock enable |

## GPIO Port D

| Register | Address | Purpose |
|---|---:|---|
| GPIOD_MODER | `0x40020C00` | GPIO mode |
| GPIOD_OTYPER | `0x40020C04` | Output type |
| GPIOD_OSPEEDR | `0x40020C08` | Output speed |
| GPIOD_PUPDR | `0x40020C0C` | Pull-up/pull-down |
| GPIOD_IDR | `0x40020C10` | Input data |
| GPIOD_ODR | `0x40020C14` | Output data |
| GPIOD_BSRR | `0x40020C18` | Bit set/reset |

---

# Debugging Methodology

Each fault was investigated using the following process:

```text
                  Symptom
                     |
                     v
              Form hypothesis
                     |
                     v
              Inspect register
                     |
                     v
           Compare expected/actual
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
```

## Debugging Principle

> Change one variable at a time and use debugger evidence to prove
> the root cause.

The objective is to avoid randomly changing multiple parts of the
firmware until the hardware starts working.

---

# Fault 1 — Wrong GPIO Peripheral Clock

## Fault Injection

The correct configuration is:

```c
RCC_AHB1ENR |= (1U << 3);
```

The fault was introduced by changing it to:

```c
RCC_AHB1ENR |= (1U << 2);
```

## Analysis

`RCC_AHB1ENR` contains the GPIO clock-enable bits:

```text
Bit 2 → GPIOCEN
Bit 3 → GPIODEN
```

The firmware therefore enabled the GPIOC clock instead of the
GPIOD clock.

## Debug Register

```text
RCC_AHB1ENR
Address: 0x40023830
```

The debugger can be used to verify:

```text
Bit 2 = 1
Bit 3 = 0
```

## Symptom

LD3 does not operate as expected.

## Root Cause

Incorrect RCC peripheral clock-enable bit.

## Fix

```c
RCC_AHB1ENR |= (1U << 3);
```

## Verification

Verify that:

```text
GPIODEN = 1
```

and confirm the expected LED behaviour.

## Lesson

Before debugging GPIO configuration, verify that the clock for the
intended peripheral is enabled.

---

# Fault 2 — Wrong GPIO Mode

## Fault Injection

The correct PD13 configuration is:

```c
GPIOD_MODER &= ~(3U << 26);
GPIOD_MODER |=  (1U << 26);
```

The fault was introduced by removing the second operation:

```c
GPIOD_MODER &= ~(3U << 26);
```

## Analysis

PD13 uses:

```text
MODER[27:26]
```

GPIO mode encoding:

```text
00 → Input
01 → General-purpose output
10 → Alternate function
11 → Analog
```

The resulting configuration is:

```text
MODER[27:26] = 00
```

Therefore:

```text
PD13 = Input
```

instead of:

```text
PD13 = General-purpose output
```

## Symptom

PD13 does not behave as a GPIO output.

LD3 does not respond as expected.

## Root Cause

Incorrect GPIO mode configuration.

## Fix

```c
GPIOD_MODER &= ~(3U << 26);
GPIOD_MODER |=  (1U << 26);
```

## Verification

Inspect:

```text
MODER[27:26] = 01
```

and verify the GPIO output behaviour.

## Lesson

When a GPIO output does not behave correctly, verify MODER
before investigating the output state.

---

# Fault 3 — Wrong GPIO Pin

## Fault Injection

Expected:

```c
GPIOD_BSRR = (1U << 13);
```

Injected:

```c
GPIOD_BSRR = (1U << 12);
```

## Analysis

The GPIO peripheral remains Port D because the firmware is still
accessing:

```text
GPIOD_BSRR
```

Only the pin number changed:

```text
1U << 13 → PD13
1U << 12 → PD12
```

The configuration therefore contains a mismatch:

```text
MODER → PD13 configured as output

BSRR  → PD12 selected for the output operation
```

## Symptom

LD3 does not respond as expected.

## Root Cause

Incorrect GPIO pin number.

## Fix

```c
GPIOD_BSRR = (1U << 13);
```

## Verification

Inspect the GPIO output state and verify that the intended
PD13 signal changes.

## Lesson

A correctly configured GPIO peripheral can still control the
wrong physical pin.

---

# Fault 4 — Wrong GPIO Base Address

## Correct Configuration

```c
#define GPIOD_BASE 0x40020C00UL
```

## Fault Injection

```c
#define GPIOD_BASE 0x40020800UL
```

## Analysis

The firmware still compiles because the value is a valid memory
address.

However, the address corresponds to a different GPIO peripheral
in the STM32F407 memory map.

This demonstrates:

```text
Valid C code
     ≠
Correct hardware access
```

The peripheral base address must therefore be verified against
the STM32F407 memory map.

## Debugging Approach

Determine the actual peripheral associated with:

```text
0x40020800
```

using the STM32F407 reference manual.

Then compare it with the expected GPIOD base:

```text
Expected GPIOD base:
0x40020C00
```

## Root Cause

Incorrect GPIO peripheral base address.

## Fix

```c
#define GPIOD_BASE 0x40020C00UL
```

## Verification

Verify that the calculated register addresses now correspond
to GPIO Port D.

For example:

```text
GPIOD_BASE + BSRR offset

0x40020C00 + 0x18
= 0x40020C18
```

## Lesson

A valid memory address does not necessarily represent the
peripheral you intended to access.

Always verify:

```text
Peripheral
    ↓
Base address
    ↓
Register offset
    ↓
Final register address
```

---

# Fault 5 — Wrong BSRR Reset Bit

## Correct Operation

To reset PD13, the BSRR reset bit is:

```text
Reset bit = Pin number + 16
          = 13 + 16
          = 29
```

Correct operation:

```c
GPIOD_BSRR = (1U << 29);
```

## Fault Injection

```c
GPIOD_BSRR = (1U << 28);
```

## Analysis

The reset pin can be calculated as:

```text
28 - 16 = 12
```

Therefore:

```text
BSRR bit 28 → reset PD12

instead of:

BSRR bit 29 → reset PD13
```

## Symptom

The intended PD13 output state is not reset as expected.

## Root Cause

Incorrect BSRR reset-bit position.

## Fix

```c
GPIOD_BSRR = (1U << 29);
```

## Verification

Inspect:

```text
GPIOD_ODR
Address: 0x40020C14
```

and verify the state of:

```text
ODR[13]
```

## Lesson

Bit-position errors can produce valid C code while controlling
the wrong hardware signal.

---

# Fault Summary

| # | Fault | Area | Root Cause | Corrective Action |
|---|---|---|---|---|
| 1 | Wrong GPIO clock | `RCC_AHB1ENR` | GPIOC enabled instead of GPIOD | Set bit 3 |
| 2 | Wrong GPIO mode | `GPIOD_MODER` | PD13 configured as input | Set `MODER[27:26] = 01` |
| 3 | Wrong GPIO pin | `GPIOD_BSRR` | PD12 selected instead of PD13 | Use bit 13 |
| 4 | Wrong base address | GPIO memory map | Wrong peripheral accessed | Use `0x40020C00` |
| 5 | Wrong BSRR reset bit | `GPIOD_BSRR` | PD12 reset instead of PD13 | Use bit 29 |

---

# Key Debugging Lessons

This project demonstrates that a GPIO failure can originate at
multiple layers:

```text
Clock
  ↓
Peripheral
  ↓
Base Address
  ↓
Register
  ↓
Configuration
  ↓
Pin
  ↓
Bit Position
  ↓
Physical Hardware
```

The most important skill developed is the ability to move from:

```text
Symptom
   ↓
Register evidence
   ↓
Root cause
   ↓
Fix
   ↓
Verification
```

without relying on trial and error.

---

# GPIO Debugging Checklist

When a GPIO-controlled device does not behave as expected:

```text
[1] Is the CPU executing?
          |
          v
[2] Is the peripheral clock enabled?
          |
          v
[3] Is the peripheral base address correct?
          |
          v
[4] Is the GPIO port correct?
          |
          v
[5] Is the GPIO pin correct?
          |
          v
[6] Is MODER correct?
          |
          v
[7] Is OTYPER correct?
          |
          v
[8] Is OSPEEDR correct?
          |
          v
[9] Is PUPDR correct?
          |
          v
[10] Is BSRR/ODR correct?
          |
          v
[11] Is the physical board mapping correct?
```

---

# Skills Demonstrated

- STM32 memory-map analysis
- Memory-mapped I/O
- Peripheral clock gating
- GPIO register configuration
- Register address calculation
- Register offset calculation
- Bit masking
- Bit shifting
- GPIO BSRR set/reset
- STM32CubeIDE debugging
- Fault injection
- Fault isolation
- Root-cause analysis
- Hardware/software correlation

---

# Project Status

- [x] GPIO output implementation
- [x] Fault 1 — Wrong GPIO clock
- [x] Fault 2 — Wrong GPIO mode
- [x] Fault 3 — Wrong GPIO pin
- [x] Fault 4 — Wrong GPIO base address
- [x] Fault 5 — Wrong BSRR reset bit
- [x] Register inspection
- [x] Debugger-based fault isolation
- [x] Root-cause analysis

---

# Next Project

## Project 02 — GPIO Input & User Button

Topics:

- GPIO input configuration
- IDR register
- Pull-up / pull-down
- User button
- Polling
- Active HIGH / active LOW
- Button debouncing

---

# References

- STM32F407xx Reference Manual — RM0090
- STM32F4DISCOVERY User Manual — UM1472
- STM32CubeIDE Debugger

---

## Author

**Pulak Mukherjee**

Embedded Firmware Engineer

Embedded C | ARM Cortex-M | Bare-Metal Firmware | RTOS
