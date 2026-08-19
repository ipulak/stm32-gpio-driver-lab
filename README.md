# STM32 GPIO Driver Lab

A hands-on bare-metal STM32 GPIO learning and debugging laboratory developed using the STM32F407VGT6 MCU and STM32F4DISCOVERY board.

This repository focuses on understanding GPIO at the register level rather than relying on STM32 HAL APIs.

The projects progressively cover GPIO output, GPIO input, switch debouncing, register-level bit manipulation, fault injection, and debugger-based root-cause analysis.

---

## Hardware & Software

| Item | Details |
|---|---|
| MCU | STM32F407VGT6 |
| CPU | ARM Cortex-M4 |
| Development Board | STM32F4DISCOVERY |
| Debugger | On-board ST-LINK |
| IDE | STM32CubeIDE |
| Programming | Bare-metal C |
| HAL | Not used |
| Debugging | STM32CubeIDE / ST-LINK GDB |

---

# Learning Progression

```text
Project 01
GPIO Output / LED
      |
      v
Project 01B
Fault Injection & Debugging
      |
      v
Project 02
GPIO Input / User Button
      |
      v
Project 03
Button Debouncing
      |
      v
Project 04
Register & Bit Manipulation
      |
      v
Next
EXTI + NVIC GPIO Interrupts
```

The objective is not simply to make an LED turn on.

The objective is to understand:

- How a microcontroller peripheral is enabled
- How memory-mapped registers are accessed
- How GPIO pins are configured
- How individual bits are manipulated
- How hardware behavior maps to register state
- How firmware faults can be isolated systematically
- How to use a debugger to prove the root cause

---

# Repository Structure

```text
stm32-gpio-driver-lab/
|
├── README.md
|
├── gpio_01_led_baremetal/
|   ├── Inc/
|   ├── Src/
|   ├── Startup/
|   └── ...
|
├── gpio_01b_fault_injection/
|   ├── Inc/
|   ├── Src/
|   └── ...
|
├── gpio_02_button_input/
|   ├── Inc/
|   ├── Src/
|   ├── Startup/
|   └── ...
|
├── gpio_03_button_debounce/
|   ├── Inc/
|   ├── Src/
|   ├── Startup/
|   └── ...
|
└── gpio_04_register_bit_manipulation/
    ├── Inc/
    ├── Src/
    ├── Startup/
    └── ...
```

---

# GPIO Architecture

The STM32F407 GPIO peripheral is memory mapped.

The firmware accesses GPIO registers by using their peripheral base address plus register offsets.

For GPIO Port D:

```text
GPIOD Base Address
        |
        v
   0x40020C00
        |
        +---- MODER
        +---- OTYPER
        +---- OSPEEDR
        +---- PUPDR
        +---- IDR
        +---- ODR
        +---- BSRR
```

This project deliberately avoids high-level GPIO APIs in order to understand the underlying hardware.

---

# Important GPIO Registers

## RCC_AHB1ENR

Address:

```text
0x40023830
```

Used to enable the clock for AHB1 peripherals.

For GPIO:

```text
Bit 0  -> GPIOAEN
Bit 1  -> GPIOBEN
Bit 2  -> GPIOCEN
Bit 3  -> GPIODEN
...
```

For Port D:

```c
RCC_AHB1ENR |= (1U << 3);
```

---

# GPIOD Register Map

GPIOD base address:

```text
0x40020C00
```

| Register | Offset | Address | Purpose |
|---|---:|---:|---|
| MODER | 0x00 | 0x40020C00 | GPIO mode |
| OTYPER | 0x04 | 0x40020C04 | Output type |
| OSPEEDR | 0x08 | 0x40020C08 | Output speed |
| PUPDR | 0x0C | 0x40020C0C | Pull-up / pull-down |
| IDR | 0x10 | 0x40020C10 | Input data |
| ODR | 0x14 | 0x40020C14 | Output data |
| BSRR | 0x18 | 0x40020C18 | Bit set/reset |

---

# Project 01 — GPIO Output / LED

Directory:

```text
gpio_01_led_baremetal/
```

## Objective

Configure PD13 as a GPIO output and control the LD3 orange LED on the STM32F4DISCOVERY board.

## GPIO Configuration

PD13 uses:

```text
MODER[27:26]
```

GPIO mode encoding:

```text
00 -> Input
01 -> General-purpose output
10 -> Alternate function
11 -> Analog
```

Therefore:

```c
GPIOD_MODER &= ~(3U << 26);
GPIOD_MODER |=  (1U << 26);
```

The project also demonstrates:

- RCC clock enable
- GPIO mode configuration
- Output type
- Output speed
- Pull-up/pull-down configuration
- GPIO output control
- Register inspection using the debugger

## Result

```text
PD13 HIGH -> LD3 ON
PD13 LOW  -> LD3 OFF
```

---

# Project 01B — GPIO Fault Injection & Debugging

Directory:

```text
gpio_01b_fault_injection/
```

This project extends the basic GPIO LED project by deliberately introducing firmware faults and debugging them using register inspection and hardware behavior.

## Debugging Methodology

```text
             Symptom
                |
                v
        Form a hypothesis
                |
                v
        Inspect registers
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

## Faults Investigated

### Fault 1 — Wrong GPIO Clock

Correct:

```c
RCC_AHB1ENR |= (1U << 3);
```

Fault:

```c
RCC_AHB1ENR |= (1U << 2);
```

Bit 2 enables GPIOC while bit 3 enables GPIOD.

**Root Cause:** The GPIOC peripheral clock was enabled instead of the GPIOD clock.

---

### Fault 2 — Wrong GPIO Mode

PD13 requires:

```text
MODER[27:26] = 01
```

If the output configuration is omitted:

```text
MODER[27:26] = 00
```

PD13 becomes an input.

**Root Cause:** Incorrect GPIO mode configuration.

---

### Fault 3 — Wrong GPIO Pin

Expected:

```c
GPIOD_BSRR = (1U << 13);
```

Fault:

```c
GPIOD_BSRR = (1U << 12);
```

The firmware accesses Port D correctly but controls PD12 instead of PD13.

**Root Cause:** Incorrect GPIO pin selection.

---

### Fault 4 — Wrong GPIO Base Address

Correct:

```text
GPIOD_BASE = 0x40020C00
```

An incorrect base address can still produce valid C code and compile successfully while accessing the wrong peripheral.

**Root Cause:** Incorrect peripheral base address.

---

### Fault 5 — Wrong BSRR Reset Bit

For PD13:

```text
SET bit   = 13
RESET bit = 13 + 16
          = 29
```

Correct:

```c
GPIOD_BSRR = (1U << 29);
```

Using bit 28 resets PD12 instead.

**Root Cause:** Incorrect BSRR bit calculation.

---

## Key Lesson

A firmware program can compile successfully and still access the wrong hardware.

The debugging process therefore needs to correlate:

```text
C code
  |
  v
Register address
  |
  v
Register value
  |
  v
Individual bit
  |
  v
Physical GPIO pin
  |
  v
Hardware behavior
```

---

# Project 02 — GPIO Button Input

Directory:

```text
gpio_02_button_input/
```

## Objective

Read a physical button using a GPIO input and control an LED based on the button state.

The STM32F4DISCOVERY user button is connected to:

```text
PA0
```

The LED used for output is:

```text
PD13
```

## GPIO Configuration

GPIOA clock:

```c
RCC_AHB1ENR |= (1U << 0);
```

PA0 is configured as an input:

```c
GPIOA_MODER &= ~(3U << 0);
```

The input state is read through:

```c
GPIOA_IDR
```

For PA0:

```c
GPIOA_IDR & (1U << 0)
```

The LED is controlled through PD13.

## Firmware Flow

```text
User Button
    |
    v
   PA0
    |
    v
GPIOA_IDR
    |
    v
CPU reads button state
    |
    v
PD13
    |
    v
LD3
```

## Debugging

The debugger can be used to inspect:

```text
GPIOA_IDR
GPIOA_MODER
GPIOD_ODR
```

The important observation is that the physical button state is reflected in the PA0 input-data bit.

---

# Project 03 — Button Debouncing

Directory:

```text
gpio_03_button_debounce/
```

## Objective

Demonstrate why a mechanical button cannot always be treated as a perfect digital signal.

Mechanical switches can produce multiple rapid electrical transitions when pressed or released.

This behavior is called:

```text
Switch Bounce
```

Instead of immediately accepting the first detected transition, the firmware waits for a short debounce interval and verifies the button state.

## Concept

Without debounce:

```text
Button press
     |
     v
1 0 1 0 1 1 0 1 1
     |
     v
Multiple transitions detected
```

With debounce:

```text
Button press
     |
     v
Detect transition
     |
     v
Wait for debounce interval
     |
     v
Verify stable state
     |
     v
Accept button event
```

## Current Implementation

The project uses a software delay to provide a simple blocking debounce mechanism.

This approach is intentionally simple because the objective is to understand the problem before moving to interrupt-driven and non-blocking solutions.

## Limitation

A blocking delay keeps the CPU occupied during the debounce period.

For more advanced firmware, the debounce mechanism can be replaced with:

- Timer-based debounce
- SysTick-based timing
- State machines
- Interrupt-driven input handling
- Event-based GPIO processing

This project therefore provides the foundation for the later EXTI/NVIC project.

---

# Project 04 — GPIO Register Bit Manipulation

Directory:

```text
gpio_04_register_bit_manipulation/
```

## Objective

Understand GPIO register manipulation at the individual-bit level and compare ODR operations with BSRR operations.

The project uses:

```text
PD12
PD13
```

as GPIO outputs.

---

## ODR Register

Address:

```text
0x40020C14
```

The output state of each GPIO pin is represented by the corresponding ODR bit.

For PD13:

```text
ODR13 = 0 -> PD13 LOW
ODR13 = 1 -> PD13 HIGH
```

---

## Direct ODR Assignment

Example:

```c
GPIOD_ODR = (1U << 13);
```

This writes the entire ODR register.

Conceptually:

```text
ODR before
   |
   v
Replace entire register
   |
   v
Only bit 13 remains set
```

This can unintentionally modify other GPIO outputs.

---

## ODR Read-Modify-Write

Example:

```c
GPIOD_ODR |= (1U << 13);
```

Conceptually:

```text
Read ODR
   |
   v
Set bit 13
   |
   v
Write ODR
```

This preserves the state of the other bits in the register.

Similarly:

```c
GPIOD_ODR &= ~(1U << 13);
```

clears bit 13.

---

# BSRR Register

Address:

```text
0x40020C18
```

BSRR provides dedicated set and reset operations.

```text
Bits 0-15
    -> SET

Bits 16-31
    -> RESET
```

For PD13:

```text
SET   -> bit 13
RESET -> bit 29
```

Therefore:

```c
/* Set PD13 */
GPIOD_BSRR = (1U << 13);

/* Reset PD13 */
GPIOD_BSRR = (1U << 29);
```

---

# Atomic GPIO Operations

Multiple GPIO pins can be controlled through a single BSRR write.

For example:

```c
GPIOD_BSRR = (1U << 12) |
             (1U << 13);
```

sets both PD12 and PD13.

To reset both:

```c
GPIOD_BSRR = (1U << 28) |
             (1U << 29);
```

This avoids performing an ODR read-modify-write operation for each individual output change.

---

# ODR vs BSRR

| Operation | ODR | BSRR |
|---|---|---|
| Set output | Yes | Yes |
| Reset output | Yes | Yes |
| Read-modify-write required | Often | No |
| Dedicated set operation | No | Yes |
| Dedicated reset operation | No | Yes |
| Useful for atomic GPIO control | Less suitable | Yes |

The important lesson is not simply that BSRR exists, but understanding why it exists and when it is preferable to manipulating ODR.

---

# Debugger-Based Verification

The STM32CubeIDE debugger was used to inspect GPIO registers during execution.

Important observations included:

```text
GPIOD_ODR
Address: 0x40020C14
```

and:

```text
ODR13 = 1
```

when PD13 was HIGH.

After clearing PD13:

```text
ODR13 = 0
```

The debugger therefore provided direct evidence connecting the firmware operation to the GPIO hardware state.

---

# GPIO Fault & Experiment Summary

| Project | Experiment | Main Concept |
|---|---|---|
| 01 | LED output | GPIO output configuration |
| 01B | Wrong GPIO clock | RCC debugging |
| 01B | Wrong GPIO mode | MODER debugging |
| 01B | Wrong pin | Bit-position debugging |
| 01B | Wrong base address | Memory-mapped peripheral debugging |
| 01B | Wrong BSRR reset bit | Register bit calculation |
| 02 | Button input | IDR / GPIO input |
| 03 | Button debounce | Mechanical switch behavior |
| 04 | ODR assignment | Register manipulation |
| 04 | ODR `\|=` | Read-modify-write |
| 04 | BSRR SET | Dedicated bit set |
| 04 | BSRR RESET | Dedicated bit reset |
| 04 | PD12 + PD13 | Multi-bit manipulation |

---

# Key Embedded Concepts Learned

## MCU Peripheral Fundamentals

- Peripheral clock enable
- Memory-mapped peripherals
- Peripheral base addresses
- Register offsets
- Register address calculation

## GPIO

- GPIO input
- GPIO output
- GPIO mode configuration
- Push-pull output
- Output speed
- Pull-up / pull-down configuration
- Input Data Register
- Output Data Register
- Bit Set/Reset Register

## Embedded C

- Bitwise AND
- Bitwise OR
- Bitwise NOT
- Bit shifting
- Bit masks
- Read-modify-write
- `volatile`
- Register access through pointers

## Debugging

- Breakpoints
- Register inspection
- Memory address verification
- Bit-level debugging
- Fault injection
- Root-cause analysis
- Hardware/software correlation

---

# Debugging Philosophy

The main lesson from this laboratory is:

> Do not debug embedded firmware by randomly changing code until the hardware works.

Instead:

```text
Observe the symptom
       |
       v
Understand the hardware
       |
       v
Identify the expected register state
       |
       v
Inspect the actual register state
       |
       v
Compare expected vs actual
       |
       v
Find the smallest incorrect assumption
       |
       v
Fix the root cause
       |
       v
Verify on hardware
```

This methodology is applicable far beyond GPIO.

The same approach can be used when debugging:

- UART
- SPI
- I2C
- Timers
- DMA
- ADC
- Interrupt controllers
- Clock configuration
- RTOS peripherals

---

# Reference Documentation

The implementation and register analysis were based on the STM32F407 documentation:

- STM32F407xx Reference Manual — RM0090
- STM32F4DISCOVERY User Manual — UM1472
- STM32F407VGT6 Datasheet

---

# Future Work

The GPIO learning path will continue with:

```text
GPIO Polling
     |
     v
EXTI External Interrupt
     |
     v
NVIC Interrupt Controller
     |
     v
Interrupt-driven Button
     |
     v
Non-blocking Debounce
     |
     v
Timer / SysTick
     |
     v
Reusable GPIO Driver
```

The eventual objective is to evolve these learning projects into reusable bare-metal peripheral drivers suitable for larger embedded firmware systems.

---

# Project Status

| Project | Status |
|---|---|
| GPIO LED Output | Completed |
| GPIO Fault Injection & Debugging | Completed |
| GPIO Button Input | Completed |
| Button Debouncing | Completed |
| GPIO Register Bit Manipulation | Completed |
| EXTI / GPIO Interrupts | Next |

---

## Author

**Pulak Mukherjee**

Embedded Firmware Engineer | ARM Cortex-M | RTOS | Bare-Metal Firmware

---

## Disclaimer

This repository is a learning and portfolio project focused on understanding STM32 hardware and bare-metal firmware development.

The code intentionally uses direct register access instead of STM32 HAL APIs to expose the underlying peripheral behavior.
