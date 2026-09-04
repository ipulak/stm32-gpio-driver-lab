#include "stm32f407xx_reg.h"

int main(void)
{
    /* Enable TIM2 clock */
    RCC_APB1ENR |= (1U << 0);

    /* Timer prescaler: 16 MHz / (15 + 1) = 1 MHz */
    TIM2_PSC = 15;

    /* Auto-reload: 1000 ticks = 1 ms */
    TIM2_ARR = 999;

    /* Enable/start timer */
    TIM2_CR1 |= (1U << 0);

    while (1)
    {
        /* Observe TIM2_CNT with the debugger. */
    }
}
