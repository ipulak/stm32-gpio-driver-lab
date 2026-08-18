/**
 * @file    main.c
 * @brief   Entry point for the STM32F407 bare-metal GPIO LED project.
 *
 * @details
 * This application demonstrates register-level initialization of the
 * STM32F407 GPIO peripheral without using the STM32 HAL GPIO driver.
 *
 * The project initially enables the GPIOD peripheral clock and provides
 * the foundation for configuring PD13, which is connected to the LD3
 * orange user LED on the STM32F4DISCOVERY board.
 *
 * The implementation is intended for learning and debugging of:
 *  - Memory-mapped peripheral registers
 *  - RCC peripheral clock configuration
 *  - GPIO register configuration
 *  - Bit manipulation and register masking
 *  - Bare-metal firmware debugging
 *
 * @reference
 * STM32F407xx Reference Manual RM0090
 * STM32F4DISCOVERY User Manual UM1472
 */

#include "stm32f407xx_reg.h"


int main(void)
{
	/* Enabling clock for GPIOD */
	RCC_AHB1ENR |= (1U << 3);

	/* Configure PD13 as general-purpose output */
	GPIOD_MODER &= ~(3U << 26);
	GPIOD_MODER |= (1U << 26);

	/* Configure PD13 as push-pull */
	GPIOD_OTYPR &= ~(1U << 13);

	/* Configure PD13 as low speed */
	GPIOD_OSPEEDR &= ~(3U << 26);

	/* Configure PD13 as no pull up/pull down register */
	GPIOD_PUPDR &= ~(3U << 26);

	/* Set PD13 */
	//GPIOD_BSSR = (1U << 13);
	GPIOD_ODR &= ~(1U << 13);

	/* Reset PD13 */
	//GPIOD_BSSR = (1U << 29);

    /* Loop forever */
	for(;;);
}
