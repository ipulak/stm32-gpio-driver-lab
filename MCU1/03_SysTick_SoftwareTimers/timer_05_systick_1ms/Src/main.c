#include "stm32f407xx_reg.h"

volatile uint32_t system_tick = 0;

void delay_ms(uint32_t ms)
{
    uint32_t start = system_tick;

    while ((system_tick - start) < ms)
    {
        /* Wait using the SysTick time base rather than a CPU-cycle delay. */
    }
}

void SysTick_Handler(void)
{
    system_tick++;
}

int main(void)
{
    /* Enable GPIOD clock */
    RCC_AHB1ENR |= (1U << 3);

    /* Configure PD13 as output */
    GPIOD_MODER &= ~(3U << 26);
    GPIOD_MODER |= (1U << 26);

    /* 1 ms SysTick at 16 MHz */
    SYSTICK_RVR = 15999;
    SYSTICK_CVR = 0;
    SYSTICK_CSR = (1U << 0) | (1U << 1) | (1U << 2);

    while (1)
    {
        GPIOD_ODR ^= (1U << 13);
        delay_ms(500);
    }
}
