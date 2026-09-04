#include "stm32f407xx_reg.h"

volatile uint32_t system_tick = 0;
volatile uint32_t tim2_event = 0;
volatile uint32_t tim2_event_count = 0;
volatile uint32_t tim2_timestamp = 0;

void SysTick_Handler(void)
{
    system_tick++;
}

void TIM2_IRQHandler(void)
{
    if (TIM2_SR & (1U << 0))
    {
        TIM2_SR &= ~(1U << 0);
        tim2_timestamp = system_tick;
        tim2_event_count++;
        tim2_event = 1;
    }
}

int main(void)
{
    /* Enable GPIOD clock and configure PD13 as output. */
    RCC_AHB1ENR |= (1U << 3);
    GPIOD_MODER &= ~(3U << 26);
    GPIOD_MODER |= (1U << 26);

    /* 1 ms SysTick time base at 16 MHz. */
    SYSTICK_RVR = 15999;
    SYSTICK_CVR = 0;
    SYSTICK_CSR = (1U << 0) | (1U << 1) | (1U << 2);

    /* TIM2: 1 MHz counter, 10 ms update period. */
    RCC_APB1ENR |= (1U << 0);
    TIM2_PSC = 15;
    TIM2_ARR = 9999;
    TIM2_CR1 |= (1U << 0);

    /* Enable TIM2 interrupt in NVIC and TIM2 update interrupt. */
    NVIC_ISER0 |= (1U << 28);
    TIM2_DIER |= (1U << 0);

    while (1)
    {
        if (tim2_event)
        {
            tim2_event = 0;

            /* Toggle LED every 50 TIM2 events = 500 ms. */
            if ((tim2_event_count % 50U) == 0U)
            {
                GPIOD_ODR ^= (1U << 13);
            }
        }
    }
}
