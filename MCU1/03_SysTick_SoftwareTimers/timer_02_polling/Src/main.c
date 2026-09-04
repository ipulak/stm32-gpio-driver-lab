#include "stm32f407xx_reg.h"

volatile uint32_t event_count;

int main(void)
{
    RCC_APB1ENR |= (1U << 0);
    TIM2_PSC = 15;
    TIM2_ARR = 999;
    TIM2_CR1 |= (1U << 0);

    while (1)
    {
        /* Poll TIM2 update flag. */
        if (TIM2_SR & (1U << 0))
        {
            event_count++;
            TIM2_SR &= ~(1U << 0);
        }
    }
}
