# GPIO Capstone Collection

This directory contains the complete progression of the MCU1 GPIO work.

## Projects

1. `gpio_01_led_baremetal` — bare-metal GPIO output and LED control
2. `gpio_01b_fault_injection` — GPIO fault-injection and robustness exercise
3. `gpio_02_button_input` — GPIO input and button handling
4. `gpio_03_button_debounce` — software button debouncing
5. `gpio_04_register_bit_manipulation` — direct register and bit-level GPIO configuration

## Platform

- MCU: STM32F407VGT6
- Board: STM32F4 Discovery
- Approach: register-level / bare metal
- IDE: STM32CubeIDE / Eclipse

These projects are intentionally kept as separate stages so the progression from basic GPIO configuration to robust input handling and register-level reasoning is visible.