#include "stm32f407xx_reg.h"

volatile uint32_t system_tick = 0;

void SysTick_Handler(void)
{
    system_tick++;
}

int main(void)
{
    /* 16 MHz / (15999 + 1) = 1 kHz = 1 ms tick */
    SYSTICK_RVR = 15999;
    SYSTICK_CVR = 0;

    /* ENABLE | TICKINT | CLKSOURCE(processor clock) */
    SYSTICK_CSR = (1U << 0) | (1U << 1) | (1U << 2);

    while (1)
    {
        /* CPU is free to perform other work. */
    }
}
