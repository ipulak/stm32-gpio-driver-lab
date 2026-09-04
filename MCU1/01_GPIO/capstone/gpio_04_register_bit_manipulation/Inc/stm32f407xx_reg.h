/**
 * @file      stm32f407xx_reg.h
 * @brief     STM32F407 register-level peripheral definitions.
 *
 * @details
 * This header provides register address definitions and memory-mapped
 * register access macros for the STM32F407 microcontroller.
 *
 * The definitions are based on the STM32F407 reference manual (RM0090)
 *
 * @note
 * This file is intended for bare-metal firmware development and does
 * not use the STM32 HAL peripheral Drivers.
 *
 * @author     Pulak Mukherjee
 * @date       2026-08-18
 *
 */


#ifndef  STM32F407XX_REG_H
#define  STM32F407XX_REG_H

#include <stdint.h>

/* RCC Peripheral base address */
#define    RCC_BASE              0x40023800UL

/* RCC AHB1 peripheral clock enable register offset */
#define    RCC_AHB1_OFFSET       0x30UL

/* RCC AHB1 peripheral clock enable register */
#define    RCC_AHB1ENR           (*(volatile uint32_t *)(RCC_BASE + RCC_AHB1_OFFSET))

/* GPIO Port A&D peripheral base address */
#define    GPIOD_BASE            0x40020C00UL
#define    GPIOA_BASE            0x40020000UL

/* GPIO register offsets */
#define    GPIO_MODER_OFFSET    0x00UL
#define    GPIO_OTYPR_OFFSET    0x04UL
#define    GPIO_OSPEEDR_OFFSET  0x08UL
#define    GPIO_PUPDR_OFFSET    0x0CUL
#define    GPIO_BSSR_OFFSET     0x18UL
#define    GPIO_ODR_OFFSET      0x14UL
#define    GPIO_IDR_OFFSET      0X10UL
#define    GPIO_MODER_OFFSET    0x00UL

/* GPIO Port D registers */
#define    GPIOD_MODER           (*(volatile uint32_t *)(GPIOD_BASE + GPIO_MODER_OFFSET))

#define    GPIOD_OTYPR           (*(volatile uint32_t *)(GPIOD_BASE + GPIO_OTYPR_OFFSET))

#define    GPIOD_OSPEEDR         (*(volatile uint32_t *)(GPIOD_BASE + GPIO_OSPEEDR_OFFSET))

#define    GPIOD_PUPDR           (*(volatile uint32_t *)(GPIOD_BASE + GPIO_PUPDR_OFFSET))

#define	   GPIOD_BSSR            (*(volatile uint32_t *)(GPIOD_BASE + GPIO_BSSR_OFFSET))

#define	   GPIOD_ODR             (*(volatile uint32_t *)(GPIOD_BASE + GPIO_ODR_OFFSET))

#define	   GPIOA_MODER           (*(volatile uint32_t *)(GPIOA_BASE + GPIO_MODER_OFFSET))

#define	   GPIOA_IDR             (*(volatile uint32_t *)(GPIOA_BASE + GPIO_IDR_OFFSET))

#endif  /* STM32F407XX_REG_H */
