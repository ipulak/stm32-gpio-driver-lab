# MCU1 — STM32 Bare-Metal Embedded Firmware Portfolio

This directory is the structured home for the MCU1 learning path on STM32F407 / STM32F4DISCOVERY.

Each topic has one focused capstone project. Individual exercises remain useful for learning, but the capstone is the portfolio-quality deliverable for that topic.

## Structure

```text
MCU1/
├── 01_GPIO/
├── 02_EXTI_NVIC/
├── 03_SysTick_SoftwareTimers/
├── 04_HardwareTimers/
├── 05_UART/
├── 06_SPI/
├── 07_I2C/
├── 08_ADC/
├── 09_DMA/
├── 10_Cortex_M/
├── 11_RTOS/
└── 12_Embedded_System_Design/
```

## Capstone rule

Every topic contains:

```text
<topic>/capstone/
├── README.md
├── Inc/
├── Src/
├── Startup/          (when required)
├── docs/
└── tests/            (when practical)
```

The code will be added as each topic is completed and hardware-tested. Generated build output (`Debug/`, `.elf`, `.o`, `.d`, `.map`, etc.) should not be committed.

## Target

- MCU: STM32F407VGT6
- Board: STM32F4DISCOVERY
- CPU: ARM Cortex-M4
- Approach: register-level / bare-metal C
- Primary IDE: STM32CubeIDE
- Primary references: STM32F407 reference manual, datasheet, ARM Cortex-M documentation

## Learning flow

GPIO → EXTI/NVIC → SysTick/software timers → hardware timers → UART → SPI/I2C → ADC → DMA → Cortex-M → RTOS → system design.
