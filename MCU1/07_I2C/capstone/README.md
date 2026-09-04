# I2C Capstone — Sensor Monitor

**Status:** Planned.

Implement an STM32F407 I2C master driver and use it to communicate with a practical sensor. Report sensor data through the UART console.

## Key concepts
- open-drain and pull-ups
- START / repeated START / STOP
- addressing
- ACK/NACK
- status/error handling
- timeout and bus recovery

## Acceptance
The firmware must detect the device, read a measurement periodically, handle communication errors, and report results over UART.