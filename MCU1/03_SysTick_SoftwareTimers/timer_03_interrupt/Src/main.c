#include "stm32f407xx_reg.h"

volatile uint32_t event_count;

void TIM2_IRQHandler(void)
{
    if (TIM2_SR & (1U << 0))
    {
        event_count++;
        TIM2_SR &= ~(1U << 0);
    }
}

int main(void)
{
    RCC_APB1ENR |= (1U << 0);
    TIM2_PSC = 15;
    TIM2_ARR = 999;
    TIM2_CR1 |= (1U << 0);

    /* TIM2 IRQ = 28 on Cortex-M4 STM32F4 */
    NVIC_ISER0 |= (1U << 28);
    TIM2_DIER |= (1U << 0);

    while (1)
    {
        /* CPU is free to perform other work. */
    }
}
